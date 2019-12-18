#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_61__   TYPE_9__ ;
typedef  struct TYPE_60__   TYPE_8__ ;
typedef  struct TYPE_59__   TYPE_7__ ;
typedef  struct TYPE_58__   TYPE_6__ ;
typedef  struct TYPE_57__   TYPE_5__ ;
typedef  struct TYPE_56__   TYPE_4__ ;
typedef  struct TYPE_55__   TYPE_3__ ;
typedef  struct TYPE_54__   TYPE_2__ ;
typedef  struct TYPE_53__   TYPE_29__ ;
typedef  struct TYPE_52__   TYPE_1__ ;
typedef  struct TYPE_51__   TYPE_18__ ;
typedef  struct TYPE_50__   TYPE_17__ ;
typedef  struct TYPE_49__   TYPE_16__ ;
typedef  struct TYPE_48__   TYPE_15__ ;
typedef  struct TYPE_47__   TYPE_14__ ;
typedef  struct TYPE_46__   TYPE_13__ ;
typedef  struct TYPE_45__   TYPE_12__ ;
typedef  struct TYPE_44__   TYPE_11__ ;
typedef  struct TYPE_43__   TYPE_10__ ;

/* Type definitions */
struct TYPE_44__ {TYPE_10__* fields; } ;
struct TYPE_49__ {int /*<<< orphan*/  typeid; int /*<<< orphan*/  kind; TYPE_11__ aggregate; } ;
typedef  TYPE_16__ Type ;
struct TYPE_61__ {size_t num_args; TYPE_18__** args; TYPE_18__* expr; } ;
struct TYPE_60__ {TYPE_18__* expr; int /*<<< orphan*/  type; } ;
struct TYPE_59__ {int /*<<< orphan*/  mod; int /*<<< orphan*/  val; } ;
struct TYPE_58__ {size_t end; size_t start; int /*<<< orphan*/  suffix; } ;
struct TYPE_57__ {size_t suffix; scalar_t__ val; int /*<<< orphan*/  mod; } ;
struct TYPE_56__ {TYPE_18__* expr; } ;
struct TYPE_55__ {int /*<<< orphan*/  op; int /*<<< orphan*/  post; int /*<<< orphan*/  expr; } ;
struct TYPE_54__ {int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct TYPE_53__ {long long ll; } ;
struct TYPE_52__ {TYPE_18__* else_expr; TYPE_18__* then_expr; TYPE_18__* cond; } ;
struct TYPE_48__ {TYPE_18__* right; int /*<<< orphan*/  op; TYPE_18__* left; } ;
struct TYPE_47__ {TYPE_18__* expr; int /*<<< orphan*/  op; } ;
struct TYPE_46__ {char* name; TYPE_18__* expr; } ;
struct TYPE_45__ {TYPE_18__* index; TYPE_18__* expr; } ;
struct TYPE_51__ {int kind; TYPE_3__ modify; TYPE_2__ offsetof_field; struct TYPE_51__* typeof_type; struct TYPE_51__* typeof_expr; int /*<<< orphan*/  alignof_type; struct TYPE_51__* alignof_expr; int /*<<< orphan*/  sizeof_type; struct TYPE_51__* sizeof_expr; TYPE_1__ ternary; TYPE_15__ binary; TYPE_14__ unary; TYPE_13__ field; TYPE_12__ index; TYPE_9__ call; TYPE_8__ cast; int /*<<< orphan*/  name; TYPE_7__ str_lit; TYPE_6__ float_lit; TYPE_5__ int_lit; TYPE_4__ paren; } ;
struct TYPE_50__ {int /*<<< orphan*/  kind; } ;
struct TYPE_43__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_17__ Sym ;
typedef  TYPE_18__ Expr ;

/* Variables and functions */
#define  EXPR_ALIGNOF_EXPR 153 
#define  EXPR_ALIGNOF_TYPE 152 
#define  EXPR_BINARY 151 
#define  EXPR_CALL 150 
#define  EXPR_CAST 149 
#define  EXPR_COMPOUND 148 
#define  EXPR_FIELD 147 
#define  EXPR_FLOAT 146 
#define  EXPR_INDEX 145 
#define  EXPR_INT 144 
#define  EXPR_MODIFY 143 
#define  EXPR_NAME 142 
#define  EXPR_NEW 141 
#define  EXPR_OFFSETOF 140 
#define  EXPR_PAREN 139 
#define  EXPR_SIZEOF_EXPR 138 
#define  EXPR_SIZEOF_TYPE 137 
#define  EXPR_STR 136 
#define  EXPR_TERNARY 135 
#define  EXPR_TYPEOF_EXPR 134 
#define  EXPR_TYPEOF_TYPE 133 
#define  EXPR_UNARY 132 
#define  MOD_BIN 131 
#define  MOD_CHAR 130 
#define  MOD_HEX 129 
 int /*<<< orphan*/  MOD_MULTILINE ; 
#define  MOD_OCT 128 
 int /*<<< orphan*/  SUFFIX_D ; 
 int /*<<< orphan*/  SYM_TYPE ; 
 int /*<<< orphan*/  TYPE_PTR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_char (char) ; 
 int /*<<< orphan*/  gen_expr_compound (TYPE_18__*) ; 
 int /*<<< orphan*/  gen_expr_new (TYPE_18__*) ; 
 int /*<<< orphan*/  gen_intrinsic (TYPE_17__*,TYPE_18__*) ; 
 int /*<<< orphan*/  gen_paren_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_str (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_typeid (TYPE_16__*) ; 
 int /*<<< orphan*/  genf (char*,...) ; 
 int /*<<< orphan*/  get_gen_name (TYPE_17__*) ; 
 int /*<<< orphan*/  get_gen_name_or_default (TYPE_18__*,int /*<<< orphan*/ ) ; 
 TYPE_17__* get_resolved_sym (TYPE_18__*) ; 
 TYPE_16__* get_resolved_type (TYPE_18__*) ; 
 TYPE_29__ get_resolved_val (TYPE_18__*) ; 
 int /*<<< orphan*/  is_aggregate_type (TYPE_16__*) ; 
 int is_implicit_any (TYPE_18__*) ; 
 int /*<<< orphan*/  is_intrinsic (TYPE_17__*) ; 
 TYPE_16__* pointer_promo_type (TYPE_18__*) ; 
 int /*<<< orphan*/  token_kind_name (int /*<<< orphan*/ ) ; 
 char** token_suffix_names ; 
 TYPE_16__* type_conv (TYPE_18__*) ; 
 int /*<<< orphan*/  type_to_cdecl (TYPE_16__*,char*) ; 
 int /*<<< orphan*/  typespec_to_cdecl (int /*<<< orphan*/ ,char*) ; 
 TYPE_16__* unqualify_type (TYPE_16__*) ; 

void gen_expr(Expr *expr) {
    Type *type = NULL;
    Type *conv = type_conv(expr);
    if (conv) {
        genf("(%s)(", type_to_cdecl(conv, ""));
    }
    bool gen_any = is_implicit_any(expr);
    if (gen_any) {
        type = get_resolved_type(expr);
        genf("(any){(%s[]){", type_to_cdecl(type, ""));
    }
    switch (expr->kind) {
    case EXPR_PAREN:
        genf("(");
        gen_expr(expr->paren.expr);
        genf(")");
        break;
    case EXPR_INT: {
        const char *suffix_name = token_suffix_names[expr->int_lit.suffix];
        switch (expr->int_lit.mod) {
        case MOD_BIN:
        case MOD_HEX:
            genf("0x%llx%s", expr->int_lit.val, suffix_name);
            break;
        case MOD_OCT:
            genf("0%llo%s", expr->int_lit.val, suffix_name);
            break;
        case MOD_CHAR:
            gen_char((char)expr->int_lit.val);
            break;
        default:
            genf("%llu%s", expr->int_lit.val, suffix_name);
            break;
        }
        break;
    }
    case EXPR_FLOAT: {
        bool is_double = expr->float_lit.suffix == SUFFIX_D;
        size_t len = expr->float_lit.end - expr->float_lit.start;
        genf("%.*s%s", is_double ? len-1 : len, expr->float_lit.start, is_double ? "" : "f");
        break;
    }
    case EXPR_STR:
        gen_str(expr->str_lit.val, expr->str_lit.mod == MOD_MULTILINE);
        break;
    case EXPR_NAME:
        genf("%s", get_gen_name_or_default(expr, expr->name));
        break;
    case EXPR_CAST:
        genf("(%s)(", typespec_to_cdecl(expr->cast.type, ""));
        gen_expr(expr->cast.expr);
        genf(")");
        break;
    case EXPR_CALL: {
        Sym *sym = get_resolved_sym(expr->call.expr);
        if (is_intrinsic(sym)) {
            gen_intrinsic(sym, expr);
        } else {
            if (sym && sym->kind == SYM_TYPE) {
                genf("(%s)", get_gen_name(sym));
            } else {
                gen_expr(expr->call.expr);
            }
            genf("(");
            for (size_t i = 0; i < expr->call.num_args; i++) {
                if (i != 0) {
                    genf(", ");
                }
                gen_expr(expr->call.args[i]);
            }
            genf(")");
        }
        break;
    }
    case EXPR_INDEX: {
        Type *type = unqualify_type(get_resolved_type(expr->index.expr));
        if (is_aggregate_type(type)) {
            gen_expr(expr->index.expr);
            genf(".");
            long long i = get_resolved_val(expr->index.index).ll;
            genf("%s", type->aggregate.fields[i].name);
        } else {
            gen_expr(expr->index.expr);
            genf("[");
            gen_expr(expr->index.index);
            genf("]");
        }
        break;
    }
    case EXPR_FIELD: {
        Sym *sym = get_resolved_sym(expr);
        if (sym) {
            genf("(%s)", get_gen_name(sym));
        } else {
            gen_expr(expr->field.expr);
            Type *type = unqualify_type(get_resolved_type(expr->field.expr));
            const char *name = expr->field.name;
            genf("%s%s", type->kind == TYPE_PTR ? "->" : ".", name);
        }
        break;
    }
    case EXPR_COMPOUND:
        gen_expr_compound(expr);
        break;
    case EXPR_UNARY:
        genf("%s(", token_kind_name(expr->unary.op));
        gen_expr(expr->unary.expr);
        genf(")");
        break;
    case EXPR_BINARY: {
        genf("(");
        Type *left_promo = pointer_promo_type(expr->binary.left);
        if (left_promo) {
            genf("(%s)", type_to_cdecl(left_promo, ""));
        }
        gen_expr(expr->binary.left);
        genf(") %s (", token_kind_name(expr->binary.op));
        Type *right_promo = pointer_promo_type(expr->binary.right);
        if (right_promo) {
            genf("(%s)", type_to_cdecl(right_promo, ""));
        }
        gen_expr(expr->binary.right);
        genf(")");
        break;
    }
    case EXPR_TERNARY:
        genf("(");
        gen_expr(expr->ternary.cond);
        genf(" ? ");
        gen_expr(expr->ternary.then_expr);
        genf(" : ");
        gen_expr(expr->ternary.else_expr);
        genf(")");
        break;
    case EXPR_SIZEOF_EXPR:
        genf("sizeof(");
        gen_expr(expr->sizeof_expr);
        genf(")");
        break;
    case EXPR_SIZEOF_TYPE:
        genf("sizeof(%s)", typespec_to_cdecl(expr->sizeof_type, ""));
        break;
    case EXPR_ALIGNOF_EXPR:
        genf("alignof(%s)", type_to_cdecl(get_resolved_type(expr->alignof_expr), ""));
        break;
    case EXPR_ALIGNOF_TYPE:
        genf("alignof(%s)", typespec_to_cdecl(expr->alignof_type, ""));
        break;
    case EXPR_TYPEOF_EXPR: {
        Type *type = get_resolved_type(expr->typeof_expr);
        assert(type->typeid);
        gen_typeid(type);
        break;
    }
    case EXPR_TYPEOF_TYPE: {
        Type *type = get_resolved_type(expr->typeof_type);
        assert(type->typeid);
        gen_typeid(type);
        break;
    }
    case EXPR_OFFSETOF:
        genf("offsetof(%s, %s)", typespec_to_cdecl(expr->offsetof_field.type, ""), expr->offsetof_field.name);
        break;
    case EXPR_MODIFY:
        if (!expr->modify.post) {
            genf("%s", token_kind_name(expr->modify.op));
        }
        gen_paren_expr(expr->modify.expr);
        if (expr->modify.post) {
            genf("%s", token_kind_name(expr->modify.op));
        }
        break;
    case EXPR_NEW:
        gen_expr_new(expr);
        break;
    default:
        assert(0);
    }
    if (gen_any) {
        genf("}, ");
        gen_typeid(type);
        genf("}");
    }
    if (conv) {
        genf(")");
    }
}