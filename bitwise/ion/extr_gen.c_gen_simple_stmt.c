#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  name; int /*<<< orphan*/  kind; int /*<<< orphan*/  base; int /*<<< orphan*/  pos; } ;
typedef  TYPE_3__ Typespec ;
struct TYPE_27__ {int /*<<< orphan*/  num_elems; } ;
typedef  TYPE_4__ Type ;
struct TYPE_25__ {TYPE_3__* right; int /*<<< orphan*/  op; TYPE_3__* left; } ;
struct TYPE_24__ {char* name; TYPE_3__* expr; int /*<<< orphan*/  is_undef; TYPE_3__* type; } ;
struct TYPE_28__ {int kind; TYPE_2__ assign; TYPE_1__ init; TYPE_3__* expr; } ;
typedef  TYPE_5__ Stmt ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_NAME ; 
#define  STMT_ASSIGN 130 
#define  STMT_EXPR 129 
#define  STMT_INIT 128 
 int /*<<< orphan*/  TOKEN_ADD_ASSIGN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gen_expr (TYPE_3__*) ; 
 int /*<<< orphan*/  genf (char*,...) ; 
 char* get_gen_name_or_default (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* get_resolved_type (TYPE_3__*) ; 
 int is_incomplete_array_typespec (TYPE_3__*) ; 
 int /*<<< orphan*/  is_ptr_type (TYPE_4__*) ; 
 int /*<<< orphan*/ * new_expr_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* new_typespec_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* pointer_promo_type (TYPE_3__*) ; 
 int /*<<< orphan*/  token_kind_name (int /*<<< orphan*/ ) ; 
 TYPE_4__* type_decay (TYPE_4__*) ; 
 TYPE_4__* type_ptr (TYPE_4__*) ; 
 int /*<<< orphan*/  type_to_cdecl (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  typespec_to_cdecl (TYPE_3__*,char*) ; 
 TYPE_4__* unqualify_type (TYPE_4__*) ; 

void gen_simple_stmt(Stmt *stmt) {
    switch (stmt->kind) {
    case STMT_EXPR:
        gen_expr(stmt->expr);
        break;
    case STMT_INIT:
        if (stmt->init.type) {
            Typespec *init_typespec = stmt->init.type;
            bool incomplete = is_incomplete_array_typespec(stmt->init.type);
            if (incomplete && !stmt->init.expr) {
                Type *init_type = get_resolved_type(stmt->init.type);
                genf("%s = 0", type_to_cdecl(type_decay(init_type), stmt->init.name));
            } else {
                if (incomplete && is_ptr_type(get_resolved_type(stmt->init.expr))) {
                    genf("%s", type_to_cdecl(get_resolved_type(stmt->init.expr), stmt->init.name));
                    if (stmt->init.expr) {
                        if (!stmt->init.is_undef) {
                            genf(" = ");
                            gen_expr(stmt->init.expr);
                        }
                    } else {
                        genf(" = {0}");
                    }
                } else {
                    if (incomplete) {
                        Expr *size = new_expr_int(init_typespec->pos, get_resolved_type(stmt->init.expr)->num_elems, 0, 0);
                        init_typespec = new_typespec_array(init_typespec->pos, init_typespec->base, size);
                    }
                    genf("%s", typespec_to_cdecl(stmt->init.type, stmt->init.name));
                    if (stmt->init.expr) {
                        if (!stmt->init.is_undef) {
                            genf(" = ");
                            gen_expr(stmt->init.expr);
                        }
                    } else if (!stmt->init.is_undef) {
                        genf(" = {0}");
                    }
                }
            }
        } else {
            genf("%s = ", type_to_cdecl(unqualify_type(get_resolved_type(stmt->init.expr)), stmt->init.name));
            gen_expr(stmt->init.expr);
        }
        break;
    case STMT_ASSIGN: {
        Type *promo_type = pointer_promo_type(stmt->assign.left);
        if (promo_type) {
            assert(stmt->assign.op == TOKEN_ADD_ASSIGN);
            Type *left_type = get_resolved_type(stmt->assign.left);
            if (stmt->assign.left->kind == EXPR_NAME) {
                const char *name = get_gen_name_or_default(stmt->assign.left, stmt->assign.left->name);
                genf("%s = (char *)(%s) + ", name, name);
                gen_expr(stmt->assign.right);
            } else {
                // TODO: this is an ugly codegen template that needs to avoid both illegal aliasing and multiple evaluation.
                // However, 99.9% of use cases will use a name on the left-hand side, and we handle that cleanly.
                genf("do { %s = (%s)&(", type_to_cdecl(type_ptr(left_type), "__pp"), type_to_cdecl(type_ptr(left_type), ""));
                gen_expr(stmt->assign.left);
                genf("); *__pp = (%s)(*(char **)__pp + ", type_to_cdecl(left_type, ""));
                gen_expr(stmt->assign.right);
                genf("); } while(0)");
            }
        } else {
            gen_expr(stmt->assign.left);
            genf(" %s ", token_kind_name(stmt->assign.op));
            gen_expr(stmt->assign.right);
        }
        break;
    }
    default:
        assert(0);
    }
}