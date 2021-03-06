/**
 * Various typedefs are used instead of plain integer indices to indicate their
 * meaning. Unfortunately, C typedefs are not new types, while this would
 * probably be a safety benefit.
 *
 * \typedef{File}: A file known to the compiler. Probably its contents will
 * be processed.
 *
 * \typedef{String}: A String. We use string for most of the string handling
 * because of three reasons: 1) Ease of memory management, 2) Saving working
 * memory, 3) (Probably?) more Efficient equality checks. On the other hand,
 * the disadvantage is that we cannot easily drop a string that was interned.
 *
 * \typedef{Token}: A Token is a syntactical entity as seen by the compiler's
 * language parser. For example, an identifier, such as `xyz`, an integer
 * literal such as `9`, a string literal such as `"a string"`, or an operator
 * such as `++`. See \ref{SymbolKind}.
 *
 * \typedef{Symbol}: A symbol is a name for a user-created artifact. See also
 * \ref{SymbolKind}.
 *
 * \typedef{Symref}: A symref is a reference to a (hopefully, existing) user-
 * created artifact. Syntactically the symbol is referenced by writing the name
 * of the symbol. It's the compilers task to match up referenced with referenced
 * symbols.
 *
 * \typedef{Scope}: A scope is an abstract container for symbol definitions. In
 * the parsing phase a tree (or DAG?) of scopes is built up. Symbol lookup is
 * done starting in a particular scope and looking for the symbol recursively in
 * the parent scopes until a match is found. See also \ref{ScopeKind}.
 *
 * \typedef{Data}: The result of parsing a data declaration. See also
 * \ref{DataInfo}.
 *
 * \typedef{Array}: The result of parsing an array definition. See also
 * \ref{ArrayInfo}.
 *
 * \typedef{Proc}: The result of parsing a proc definition. See also
 * \ref{ProcInfo}.
 *
 * \typedef{Param}: The result of parsing a procedure parameter as part of a
 * proc definition. See also \ref{ParamInfo}
 *
 * \typedef{Expr}: The result of parsing an expression, as part of a statement.
 * See also \ref{ExprInfo}.
 *
 * \typedef{CompoundStmt}: The result of parsing a compound statement (a number
 * of statements enclosed in curly braces \{\}, as part of parsing a proc
 * definition. See also \ref{CompoundStmtInfo}.
 *
 * \typedef{ExprStmt}: The result of parsing an expression statement, a kind of
 * statement that commands a computation. See also \ref{ExprStmtInfo}.
 *
 * \typedef{IfStmt}: The result of parsing an if statement. See also
 * \ref{IfStmtInfo}.
 *
 * \typedef{ForStmt}: The result of parsing a for statement. See also
 * \ref{ForStmtInfo}.
 *
 * \typedef{WhileStmt}: The result of parsing a while statement. See also
 * \ref{WhileStmtInfo}.
 *
 * \typedef{Stmt}: The result of parsing a statement, which can be any of the
 * previous kinds of statements. See also \ref{StmtInfo}.
 */

typedef int File;
typedef int String;
typedef int Token;
typedef int Type;
typedef int Symbol;
typedef int Symref;
typedef int Scope;
typedef int Data;
typedef int Array;
typedef int Proc;
typedef int Param;
typedef int Expr;
typedef int CompoundStmt;
typedef int ExprStmt;
typedef int IfStmt;
typedef int ForStmt;
typedef int WhileStmt;
typedef int Stmt;

/**
 * \enum{TokenKind}: Token kinds (lexical syntax)
 *
 * \enum{ConstStrKind}: Constant strings that get interned at startup as an
 * optimization
 *
 * \enum{UnopKind}: Unary operators. Currently all correspond to single tokens,
 * like ~, !, &, ++, and others.
 *
 * \enum{BinopKind}: Binary operators. Currently all correspond to single
 * tokens, like =, ==, -, +, *, /, and others.
 *
 * \enum{ExprKind}: Expression kinds. Expressions are (typically?) contained in
 * statements.
 *
 * \enum{StmtKind}: Statement kinds. Procedure bodies are made up of statements.
 * One kind of statement is the compound statement, which contains an arbitrary
 * number of other child statements in curly braces.
 *
 * \enum{ScopeKind}: Scope kinds. For now, there are global and block scopes.
 * The latter exist inside procedures.
 *
 * \enum{SymbolKind}: Symbol kinds. Symbols are names for artifacts that are
 * builtin or defined by the programmer. These artifacts can be types, data, or
 * procedures. A symbol is a name (string) together with a scope (definition
 * namespace), and an artifact kind and index. The kind and index identify the
 * artifact that the symbol names.
 *
 * \enum{TypeKind}: Type kinds. Types are needed to compile efficient machine
 * code. There are built-in and user-defined types. The builtin types are
 * (mostly?) various kinds of integers and pointers (which are integers as
 * well). The user-defined types, such as entities, arrays, or procedures, are
 * made up from other existing types (which may themselves be user-defined, or
 * built-in ones). Pointers to other types are implemented as types of kind
 * TYPE_REFERENCE, and these types contain symbol references, which must resolve
 * to SYMBOL_TYPE symbols.
 */

enum TokenKind {
        TOKTYPE_WORD,
        TOKTYPE_INTEGER,
        TOKTYPE_LEFTPAREN,
        TOKTYPE_RIGHTPAREN,
        TOKTYPE_LEFTBRACE,
        TOKTYPE_RIGHTBRACE,
        TOKTYPE_LEFTBRACKET,
        TOKTYPE_RIGHTBRACKET,
        TOKTYPE_DOT,
        TOKTYPE_MINUS,
        TOKTYPE_PLUS,
        TOKTYPE_ASTERISK,
        TOKTYPE_SLASH,
        TOKTYPE_DOUBLEMINUS,
        TOKTYPE_DOUBLEPLUS,
        TOKTYPE_COMMA,
        TOKTYPE_SEMICOLON,
        TOKTYPE_COLON,
        TOKTYPE_AMPERSAND,
        TOKTYPE_PIPE,
        TOKTYPE_CARET,
        TOKTYPE_TILDE,
        TOKTYPE_BANG,
        TOKTYPE_ASSIGNEQUALS,
        TOKTYPE_DOUBLEEQUALS,
};

enum ConstStrKind {
        CONSTSTR_IF,
        CONSTSTR_WHILE,
        CONSTSTR_FOR,
        CONSTSTR_RETURN,
        CONSTSTR_PROC,
        CONSTSTR_DATA,
        CONSTSTR_ENTITY,
        CONSTSTR_ARRAY,
        NUM_CONSTSTRS,
};

enum UnopKind {
        UNOP_INVERTBITS,
        UNOP_NOT,
        UNOP_ADDRESSOF,
        UNOP_DEREF,
        UNOP_NEGATIVE,
        UNOP_POSITIVE,
        UNOP_PREDECREMENT,
        UNOP_PREINCREMENT,
        UNOP_POSTDECREMENT,
        UNOP_POSTINCREMENT,
        NUM_UNOPS,
};

enum BinopKind {
        BINOP_ASSIGN,
        BINOP_EQUALS,
        BINOP_MINUS,
        BINOP_PLUS,
        BINOP_MUL,
        BINOP_DIV,
        BINOP_BITAND,
        BINOP_BITOR,
        BINOP_BITXOR,
        NUM_BINOPS,
};

enum ExprKind {
        EXPR_LITERAL,
        EXPR_SYMREF,
        EXPR_UNOP,
        EXPR_BINOP,
        EXPR_MEMBER,
        EXPR_SUBSCRIPT,
        EXPR_CALL,
};

enum StmtKind {
        STMT_IF,
        STMT_FOR,
        STMT_WHILE,
        STMT_RETURN,
        STMT_EXPR,
        STMT_COMPOUND,
        STMT_DATA,
        STMT_ARRAY,
};

enum ScopeKind {
        SCOPE_GLOBAL,
        SCOPE_PROC,
};

enum SymbolKind {
        SYMBOL_TYPE,
        SYMBOL_DATA,
        SYMBOL_ARRAY,
        SYMBOL_PROC,
        SYMBOL_PARAM,
};

enum TypeKind {
        TYPE_BASE,
        TYPE_ENTITY,
        TYPE_ARRAY,
        TYPE_PROC,
        TYPE_REFERENCE,
};


/**
 * \struct{StringToBeInterned} Static information used at program initialization
 * time when constant strings get interned.
 *
 * \struct{BasetypeToBeInitialized}: Static information used at program
 * initialization time when base types get registered.
 *
 * \struct{ToktypeToPrefixUnop}: Static information used for mapping tokens to
 * prefix operators (if possible).
 *
 * \struct{ToktypeToPostfixUnop}: Static information used for mapping tokens to
 * postfix operators (if possible).
 *
 * \struct{ToktypeToBinop}: Static information used for mapping tokens to binary
 * operators (if possible).
 *
 * \struct{UnopInfo}: Static information about the syntactic nature of unary
 * operators. Contains the string representation of the operator, as well as
 * whether it is a prefix or postfix operator.
 *
 * \struct{BinopInfo}: Static information about the syntactic nature of binary
 * operators. Contains the string representation of the operator, as well its
 * the precedence value for deciding associativity in the absences of
 * parentheses.
 *
 * \struct{SymbolInfo}: Represents a name given to one of the various entity
 * that the programmer can define, such as data items, array items, or types.
 * This struct contains the name and scope of the symbol as well as a reference
 * to the named item (by means of a kind tag and union containing an index for
 * each possible kind).
 *
 * \struct{SymrefInfo}: Represents a reference to a symbol that is (hopefully)
 * defined somewhere else in the code. The reference itself can occur at various
 * places in the grammar, such as as expressions or type definitions.
 *
 * \struct{DataInfo}: Result from parsing a `data` declaration. Contains the
 * name, scope, and type of the data item.
 *
 * \struct{ArrayInfo}: Result from parsing an `array` declaration. Contains the
 * name and scope of the data item as well as the type of indices needed and
 * the type of elements contained.
 *
 * \struct{ProcInfo}: Result from parsing a `proc` declaration.
 */

struct StringToBeInterned {
        int constant;  // CONSTSTR_
        const char *string;
};

struct BasetypeToBeInitialized {
        const char *name;
        int size;
};

struct ToktypeToPrefixUnop {
        int ttype;
        int optype;
};

struct ToktypeToPostfixUnop {
        int ttype;
        int optype;
};

struct ToktypeToBinop {
        int ttype;
        int optype;
};

struct UnopInfo {
        int isprefix;
        char *str;
};

struct BinopInfo {
        int prec;
        char *str;
};

struct Alloc {
        int cap;
};

struct FileInfo {
        String filepath;
        int size;
        unsigned char *buf;
        struct Alloc bufAlloc;
};

struct StringInfo {
        int pos;  // offset in character buffer
        String next;  // next string in chain
};

struct StringBucketInfo {
        String firstString;
};

struct WordTokenInfo {
        String string;
};

struct IntegerTokenInfo {
        long long value;
};

struct StringTokenInfo {
        String value;
};

struct TokenInfo {
        File file;
        int offset;
        int kind;
        union {
                struct WordTokenInfo tWord;
                struct IntegerTokenInfo tInteger;
                struct StringTokenInfo tString;
        };
};

struct SymbolInfo {
        String name;
        Scope scope;
        int kind;  // SYMBOL_
        union {
                Type tType;
                Data tData;
                Array tArray;
                Proc tProc;
                Param tParam;
        };
};

struct SymrefInfo {
        String name;
        Scope refScope;
        Token tok;
        Symbol sym;  // only valid after symbol resolution
};

struct BasetypeInfo {
        String name;
        int size;
};

struct EntitytypeInfo {
        String name;
        Type tp;
};

struct ArraytypeInfo {
        Type idxtp;
        Type valuetp;
};

struct ProctypeInfo {
        Type rettp;
        int nargs;
        int firstParamtype; // speed-up
};

struct ParamtypeInfo {  // helper for ProctypeInfo
        Type proctp;
        Type argtp;
        int rank;
};

struct ReftypeInfo {
        Symref ref;
        Type resolvedTp;
};

struct TypeInfo {
        int kind;  // TYPE_?
        union {
                struct BasetypeInfo tBase;
                struct EntitytypeInfo tEntity;
                struct ArraytypeInfo tArray;
                struct ProctypeInfo tProc;
                struct ReftypeInfo tRef;
        };
        /* Types can have references to other types, either directly (if
         * kind == tRef) or indirectly (by being a compound of other types that
         * have references). These references can fail to resolve, in which
         * case the type is considered incomplete.
         */
        int isComplete;
};

struct DataInfo {
        Scope scope;
        Type tp;
        Symbol sym;  // back-link
};

struct ArrayInfo {
        Scope scope;
        Type tp;
        Symbol sym;  // back-link
};

struct ScopeInfo {
        Scope parentScope;
        Symbol firstSymbol; // speed-up
        int numSymbols;
        int kind;
        union {
                struct {
                        Proc proc;
                } tProc;
        };
};

struct ProcInfo {
        Type tp;
        Symbol sym;
        Scope scope;
        int nparams;
        Param firstParam;  // speed-up
        Stmt body;
};

struct ParamInfo {
        Proc proc;
        Symbol sym;
        Type tp;
        int rank;
};

struct SymrefExprInfo {
        Symref ref;
};

struct LiteralExprInfo {
        Token tok;
};

struct CallExprInfo {
        Expr callee;
        Expr firstArgIdx;  // speed-up
        int nargs;
};

struct CallArgInfo {
        Expr callExpr;
        Expr argExpr;
        int rank;
};

struct UnopExprInfo {
        int kind;
        Token tok;
        Expr expr;
};

struct BinopExprInfo {
        int kind;
        Token tok;
        Expr expr1;
        Expr expr2;
};

struct MemberExprInfo {
        Expr expr;
        String name;
};

struct SubscriptExprInfo {
        Expr expr1;
        Expr expr2;
};

struct ExprInfo {
        int kind;
        union {
                struct SymrefExprInfo tSymref;
                struct LiteralExprInfo tLiteral;
                struct CallExprInfo tCall;
                struct UnopExprInfo tUnop;
                struct BinopExprInfo tBinop;
                struct MemberExprInfo tMember;
                struct SubscriptExprInfo tSubscript;
        };
        Type tp;
};

struct CompoundStmtInfo {
        int numStatements;
        int firstChildStmtIdx;
};

struct ExprStmtInfo {
        Expr expr;
};

struct IfStmtInfo {
        Expr condExpr;
        Stmt childStmt;
};

struct ForStmtInfo {
        Stmt initStmt;
        Expr condExpr;
        Stmt stepStmt;
        Stmt childStmt;
};

struct WhileStmtInfo {
        Expr condExpr;
        Stmt childStmt;
};

struct ReturnStmtInfo {
        Expr expr;
};

struct StmtInfo {
        int kind;
        union {
                struct CompoundStmtInfo tCompound;
                struct ExprStmtInfo tExpr;
                struct IfStmtInfo tIf;
                struct WhileStmtInfo tWhile;
                struct ForStmtInfo tFor;
                struct ReturnStmtInfo tReturn;
                Data tData;
                Array tArray;
        };
};

struct ChildStmtInfo {
        Stmt parent;
        Stmt child;
        int rank;
};


#ifdef DATA_IMPL
#define DATA
#else
#define DATA extern
#endif

extern const char *const tokenKindString[];
extern const char *const exprKindString[];
extern const char *const typeKindString[];
extern const struct ToktypeToPrefixUnop toktypeToPrefixUnop[];
extern const struct ToktypeToPostfixUnop toktypeToPostfixUnop[];
extern const struct ToktypeToBinop toktypeToBinop[];
extern const struct UnopInfo unopInfo[NUM_UNOPS];
extern const struct BinopInfo binopInfo[NUM_BINOPS];
extern const struct StringToBeInterned stringsToBeInterned[NUM_CONSTSTRS];
extern const struct BasetypeToBeInitialized basetypesToBeInitialized[];
extern const int toktypeToPrefixUnopCnt;
extern const int toktypeToPostfixUnopCnt;
extern const int toktypeToBinopCnt;
extern const int basetypesToBeInitializedCnt;
DATA String constStr[NUM_CONSTSTRS];  // has initializer

/**/

DATA int doDebug;

DATA File currentFile;
DATA int currentOffset;
DATA int haveSavedChar;
DATA int savedChar;

DATA int haveSavedToken;
DATA Token savedToken;

DATA Scope globalScope;
DATA Scope currentScope;
DATA Scope scopeStack[16];
DATA int scopeStackCnt;

DATA int lexbufCnt;
DATA int strbufCnt;
DATA int stringCnt;
DATA int strBucketCnt;
DATA int fileCnt;
DATA int tokenCnt;
DATA int typeCnt;
DATA int paramtypeCnt;
DATA int symbolCnt;
DATA int dataCnt;
DATA int arrayCnt;
DATA int scopeCnt;
DATA int procCnt;
DATA int paramCnt;
DATA int symrefCnt;
DATA int exprCnt;
DATA int stmtCnt;
DATA int childStmtCnt;
DATA int callArgCnt;

DATA char *lexbuf;
DATA char *strbuf;
DATA struct StringInfo *stringInfo;
DATA struct StringBucketInfo *strBucketInfo;
DATA struct FileInfo *fileInfo;
DATA struct TokenInfo *tokenInfo;
DATA struct TypeInfo *typeInfo;
DATA struct ParamtypeInfo *paramtypeInfo;
DATA struct SymbolInfo *symbolInfo;
DATA struct DataInfo *dataInfo;
DATA struct ArrayInfo *arrayInfo;
DATA struct ScopeInfo *scopeInfo;
DATA struct ProcInfo *procInfo;
DATA struct ParamInfo *paramInfo;
DATA struct SymrefInfo *symrefInfo;
DATA struct ExprInfo *exprInfo;
DATA struct StmtInfo *stmtInfo;
DATA struct ChildStmtInfo *childStmtInfo;
DATA struct CallArgInfo *callArgInfo;

DATA struct Alloc lexbufAlloc;
DATA struct Alloc strbufAlloc;
DATA struct Alloc stringInfoAlloc;
DATA struct Alloc strBucketInfoAlloc;
DATA struct Alloc fileInfoAlloc;
DATA struct Alloc tokenInfoAlloc;
DATA struct Alloc typeInfoAlloc;
DATA struct Alloc paramtypeInfoAlloc;
DATA struct Alloc symbolInfoAlloc;
DATA struct Alloc dataInfoAlloc;
DATA struct Alloc arrayInfoAlloc;
DATA struct Alloc scopeInfoAlloc;
DATA struct Alloc procInfoAlloc;
DATA struct Alloc paramInfoAlloc;
DATA struct Alloc symrefInfoAlloc;
DATA struct Alloc exprInfoAlloc;
DATA struct Alloc stmtInfoAlloc;
DATA struct Alloc childStmtInfoAlloc;
DATA struct Alloc callArgInfoAlloc;

#ifdef DATA
#undef DATA
#endif


void read_whole_file(File file);
void mem_fill(void *ptr, int val, int size);
void mem_copy(void *dst, const void *src, int size);
int mem_compare(const void *m1, const void *m2, int size);
int cstr_length(const char *s);
int cstr_compare(const char *s1, const char *m2);
void *mem_realloc(void *ptr, int size);
void sort_array(void *ptr, int nelems, int elemsize,
                int (*compare)(const void*, const void*));




void output(const char *fmt, ...);
void _msg(UNUSED const char *filename, UNUSED int line,
          const char *loglevel, const char *fmt, ...);
void NORETURN _fatal(const char *filename, int line, const char *fmt, ...);

#define MSG(lvl, fmt, ...) _msg(__FILE__, __LINE__, lvl, fmt, ##__VA_ARGS__)
#define WARN(fmt, ...) _msg(__FILE__, __LINE__, "WARN", fmt, ##__VA_ARGS__)
#define FATAL(fmt, ...) _fatal(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define UNHANDLED_CASE() FATAL("Unhandled case!");



void _buf_init(void **ptr, struct Alloc *alloc, int elsize,
               const char *UNUSED file, int UNUSED line);
void _buf_exit(void **ptr, struct Alloc *alloc, int elsize,
               const char *UNUSED file, int UNUSED line);
void _buf_reserve(void **ptr, struct Alloc *alloc, int nelems, int elsize,
                  int clear, const char *UNUSED file, int UNUSED line);

#define BUF_INIT(buf, alloc) \
        _buf_init((void**)&(buf), &(alloc), sizeof *(buf), __FILE__, __LINE__);

#define BUF_EXIT(buf, alloc) \
        _buf_exit((void**)&(buf), &(alloc), sizeof *(buf), __FILE__, __LINE__);

#define BUF_RESERVE(buf, alloc, cnt) \
        _buf_reserve((void**)&(buf), &(alloc), (cnt), sizeof *(buf), 0, \
                     __FILE__, __LINE__);

#define BUF_RESERVE_Z(buf, alloc, cnt) \
        _buf_reserve((void**)&(buf), &(alloc), (cnt), sizeof *(buf), 1, \
                     __FILE__, __LINE__);

#define BUF_APPEND(buf, alloc, cnt, el) \
        do { \
                void *ptr = (buf); \
                int _appendpos = (cnt)++; \
                _buf_reserve(&ptr, &(alloc), _appendpos+1, sizeof *(buf), 0, \
                             __FILE__, __LINE__); \
                (buf)[_appendpos] = el; \
        } while (0)


static inline const char *string_buffer(String s)
{
        return &strbuf[stringInfo[s].pos];
}

static inline int string_length(String s)
{
        return stringInfo[s+1].pos - stringInfo[s].pos - 1;
}

static inline const char *SS(Symbol sym)
{
        return string_buffer(symbolInfo[sym].name);
}

static inline const char *SRS(Symref ref)
{
        return string_buffer(symrefInfo[ref].name);
}

static inline const char *TS(Token tok)
{
        return string_buffer(tokenInfo[tok].tWord.string);
}

static inline const char *TKS(Token tok)
{
        return tokenKindString[tokenInfo[tok].kind];
}

String intern_string(const void *buf, int len);
String intern_cstring(const char *str);


void prettyprint(void);
