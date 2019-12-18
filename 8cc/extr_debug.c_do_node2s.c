#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  kind; } ;
struct TYPE_10__ {int kind; char ival; char* fname; struct TYPE_10__* right; struct TYPE_10__* left; int /*<<< orphan*/  label; struct TYPE_10__* operand; TYPE_5__* ty; int /*<<< orphan*/  field; struct TYPE_10__* struc; int /*<<< orphan*/  stmts; struct TYPE_10__* retval; struct TYPE_10__* els; struct TYPE_10__* then; struct TYPE_10__* cond; TYPE_5__* totype; int /*<<< orphan*/  initoff; struct TYPE_10__* initval; int /*<<< orphan*/  declinit; TYPE_1__* declvar; struct TYPE_10__* body; int /*<<< orphan*/  params; int /*<<< orphan*/  args; int /*<<< orphan*/  varname; int /*<<< orphan*/  lvarinit; int /*<<< orphan*/  sval; int /*<<< orphan*/  fval; } ;
struct TYPE_9__ {char* varname; TYPE_5__* ty; } ;
typedef  TYPE_2__ Node ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
#define  AST_ADDR 179 
#define  AST_COMPOUND_STMT 178 
#define  AST_CONV 177 
#define  AST_DECL 176 
#define  AST_DEREF 175 
#define  AST_FUNC 174 
#define  AST_FUNCALL 173 
#define  AST_FUNCDESG 172 
#define  AST_FUNCPTR_CALL 171 
#define  AST_GOTO 170 
#define  AST_GVAR 169 
#define  AST_IF 168 
#define  AST_INIT 167 
#define  AST_LABEL 166 
#define  AST_LITERAL 165 
#define  AST_LVAR 164 
#define  AST_RETURN 163 
#define  AST_STRUCT_REF 162 
#define  AST_TERNARY 161 
#define  KIND_ARRAY 160 
#define  KIND_CHAR 159 
#define  KIND_DOUBLE 158 
#define  KIND_FLOAT 157 
#define  KIND_INT 156 
#define  KIND_LDOUBLE 155 
#define  KIND_LLONG 154 
#define  KIND_LONG 153 
#define  OP_A_ADD 152 
#define  OP_A_AND 151 
#define  OP_A_DIV 150 
#define  OP_A_MOD 149 
#define  OP_A_MUL 148 
#define  OP_A_OR 147 
#define  OP_A_SAL 146 
#define  OP_A_SAR 145 
#define  OP_A_SHR 144 
#define  OP_A_SUB 143 
#define  OP_A_XOR 142 
#define  OP_CAST 141 
 int const OP_EQ ; 
#define  OP_GE 140 
#define  OP_LABEL_ADDR 139 
#define  OP_LE 138 
#define  OP_LOGAND 137 
#define  OP_LOGOR 136 
#define  OP_NE 135 
#define  OP_POST_DEC 134 
#define  OP_POST_INC 133 
#define  OP_PRE_DEC 132 
#define  OP_PRE_INC 131 
#define  OP_SAL 130 
#define  OP_SAR 129 
#define  OP_SHR 128 
 int /*<<< orphan*/  a2s_declinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binop_to_string (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  error (char*) ; 
 char* node2s (TYPE_2__*) ; 
 int /*<<< orphan*/  quote_cstring (int /*<<< orphan*/ ) ; 
 char* ty2s (TYPE_5__*) ; 
 int /*<<< orphan*/  uop_to_string (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 TYPE_2__* vec_get (int /*<<< orphan*/ ,int) ; 
 int vec_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_node2s(Buffer *b, Node *node) {
    if (!node) {
        buf_printf(b, "(nil)");
        return;
    }
    switch (node->kind) {
    case AST_LITERAL:
        switch (node->ty->kind) {
        case KIND_CHAR:
            if (node->ival == '\n')      buf_printf(b, "'\n'");
            else if (node->ival == '\\') buf_printf(b, "'\\\\'");
            else if (node->ival == '\0') buf_printf(b, "'\\0'");
            else buf_printf(b, "'%c'", node->ival);
            break;
        case KIND_INT:
            buf_printf(b, "%d", node->ival);
            break;
        case KIND_LONG:
            buf_printf(b, "%ldL", node->ival);
            break;
        case KIND_LLONG:
            buf_printf(b, "%lldL", node->ival);
            break;
        case KIND_FLOAT:
        case KIND_DOUBLE:
        case KIND_LDOUBLE:
            buf_printf(b, "%f", node->fval);
            break;
        case KIND_ARRAY:
            buf_printf(b, "\"%s\"", quote_cstring(node->sval));
            break;
        default:
            error("internal error");
        }
        break;
    case AST_LABEL:
        buf_printf(b, "%s:", node->label);
        break;
    case AST_LVAR:
        buf_printf(b, "lv=%s", node->varname);
        if (node->lvarinit) {
            buf_printf(b, "(");
            a2s_declinit(b, node->lvarinit);
            buf_printf(b, ")");
        }
        break;
    case AST_GVAR:
        buf_printf(b, "gv=%s", node->varname);
        break;
    case AST_FUNCALL:
    case AST_FUNCPTR_CALL: {
        buf_printf(b, "(%s)%s(", ty2s(node->ty),
                   node->kind == AST_FUNCALL ? node->fname : node2s(node));
        for (int i = 0; i < vec_len(node->args); i++) {
            if (i > 0)
                buf_printf(b, ",");
            buf_printf(b, "%s", node2s(vec_get(node->args, i)));
        }
        buf_printf(b, ")");
        break;
    }
    case AST_FUNCDESG: {
        buf_printf(b, "(funcdesg %s)", node->fname);
        break;
    }
    case AST_FUNC: {
        buf_printf(b, "(%s)%s(", ty2s(node->ty), node->fname);
        for (int i = 0; i < vec_len(node->params); i++) {
            if (i > 0)
                buf_printf(b, ",");
            Node *param = vec_get(node->params, i);
            buf_printf(b, "%s %s", ty2s(param->ty), node2s(param));
        }
        buf_printf(b, ")");
        do_node2s(b, node->body);
        break;
    }
    case AST_GOTO:
        buf_printf(b, "goto(%s)", node->label);
        break;
    case AST_DECL:
        buf_printf(b, "(decl %s %s",
                   ty2s(node->declvar->ty),
                   node->declvar->varname);
        if (node->declinit) {
            buf_printf(b, " ");
            a2s_declinit(b, node->declinit);
        }
        buf_printf(b, ")");
        break;
    case AST_INIT:
        buf_printf(b, "%s@%d", node2s(node->initval), node->initoff, ty2s(node->totype));
        break;
    case AST_CONV:
        buf_printf(b, "(conv %s=>%s)", node2s(node->operand), ty2s(node->ty));
        break;
    case AST_IF:
        buf_printf(b, "(if %s %s",
                   node2s(node->cond),
                   node2s(node->then));
        if (node->els)
            buf_printf(b, " %s", node2s(node->els));
        buf_printf(b, ")");
        break;
    case AST_TERNARY:
        buf_printf(b, "(? %s %s %s)",
                   node2s(node->cond),
                   node2s(node->then),
                   node2s(node->els));
        break;
    case AST_RETURN:
        buf_printf(b, "(return %s)", node2s(node->retval));
        break;
    case AST_COMPOUND_STMT: {
        buf_printf(b, "{");
        for (int i = 0; i < vec_len(node->stmts); i++) {
            do_node2s(b, vec_get(node->stmts, i));
            buf_printf(b, ";");
        }
        buf_printf(b, "}");
        break;
    }
    case AST_STRUCT_REF:
        do_node2s(b, node->struc);
        buf_printf(b, ".");
        buf_printf(b, node->field);
        break;
    case AST_ADDR:  uop_to_string(b, "addr", node); break;
    case AST_DEREF: uop_to_string(b, "deref", node); break;
    case OP_SAL:  binop_to_string(b, "<<", node); break;
    case OP_SAR:
    case OP_SHR:  binop_to_string(b, ">>", node); break;
    case OP_GE:  binop_to_string(b, ">=", node); break;
    case OP_LE:  binop_to_string(b, "<=", node); break;
    case OP_NE:  binop_to_string(b, "!=", node); break;
    case OP_PRE_INC: uop_to_string(b, "pre++", node); break;
    case OP_PRE_DEC: uop_to_string(b, "pre--", node); break;
    case OP_POST_INC: uop_to_string(b, "post++", node); break;
    case OP_POST_DEC: uop_to_string(b, "post--", node); break;
    case OP_LOGAND: binop_to_string(b, "and", node); break;
    case OP_LOGOR:  binop_to_string(b, "or", node); break;
    case OP_A_ADD:  binop_to_string(b, "+=", node); break;
    case OP_A_SUB:  binop_to_string(b, "-=", node); break;
    case OP_A_MUL:  binop_to_string(b, "*=", node); break;
    case OP_A_DIV:  binop_to_string(b, "/=", node); break;
    case OP_A_MOD:  binop_to_string(b, "%=", node); break;
    case OP_A_AND:  binop_to_string(b, "&=", node); break;
    case OP_A_OR:   binop_to_string(b, "|=", node); break;
    case OP_A_XOR:  binop_to_string(b, "^=", node); break;
    case OP_A_SAL:  binop_to_string(b, "<<=", node); break;
    case OP_A_SAR:
    case OP_A_SHR:  binop_to_string(b, ">>=", node); break;
    case '!': uop_to_string(b, "!", node); break;
    case '&': binop_to_string(b, "&", node); break;
    case '|': binop_to_string(b, "|", node); break;
    case OP_CAST: {
        buf_printf(b, "((%s)=>(%s) %s)",
                   ty2s(node->operand->ty),
                   ty2s(node->ty),
                   node2s(node->operand));
        break;
    }
    case OP_LABEL_ADDR:
        buf_printf(b, "&&%s", node->label);
        break;
    default: {
        char *left = node2s(node->left);
        char *right = node2s(node->right);
        if (node->kind == OP_EQ)
            buf_printf(b, "(== ");
        else
            buf_printf(b, "(%c ", node->kind);
        buf_printf(b, "%s %s)", left, right);
    }
    }
}