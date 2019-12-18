#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ name; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ TypeField ;
struct TYPE_19__ {size_t num_fields; TYPE_3__* fields; } ;
struct TYPE_22__ {TYPE_1__ aggregate; int /*<<< orphan*/  base; } ;
typedef  TYPE_4__ Type ;
struct TYPE_20__ {scalar_t__ name; int /*<<< orphan*/  expr; } ;
struct TYPE_24__ {scalar_t__ kind; TYPE_2__ field; int /*<<< orphan*/  pos; } ;
struct TYPE_23__ {int /*<<< orphan*/  type; scalar_t__ is_lvalue; } ;
typedef  int /*<<< orphan*/  Sym ;
typedef  int /*<<< orphan*/  Package ;
typedef  TYPE_5__ Operand ;
typedef  TYPE_6__ Expr ;

/* Variables and functions */
 scalar_t__ EXPR_FIELD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  complete_type (TYPE_4__*) ; 
 int /*<<< orphan*/ * enter_package (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  is_aggregate_type (TYPE_4__*) ; 
 int is_const_type (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ptr_type (TYPE_4__*) ; 
 int /*<<< orphan*/  leave_package (int /*<<< orphan*/ *) ; 
 TYPE_5__ operand_lvalue (int /*<<< orphan*/ ) ; 
 TYPE_5__ operand_null ; 
 TYPE_5__ operand_rvalue (int /*<<< orphan*/ ) ; 
 TYPE_5__ resolve_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * resolve_name (scalar_t__) ; 
 TYPE_5__ resolve_name_operand (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_resolved_sym (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * try_resolve_package (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_const (int /*<<< orphan*/ ) ; 
 TYPE_4__* unqualify_type (int /*<<< orphan*/ ) ; 

Operand resolve_expr_field(Expr *expr) {
    assert(expr->kind == EXPR_FIELD);
    Package *package = try_resolve_package(expr->field.expr);
    if (package) {
        Package *old_package = enter_package(package);
        Sym *sym = resolve_name(expr->field.name);
        Operand operand = resolve_name_operand(expr->pos, expr->field.name);
        leave_package(old_package);
        set_resolved_sym(expr, sym);
        return operand;
    }
    Operand operand = resolve_expr(expr->field.expr);
    bool was_const_type = is_const_type(operand.type);
    Type *type = unqualify_type(operand.type);
    complete_type(type);
    if (is_ptr_type(type)) {
        operand = operand_lvalue(type->base);
        was_const_type = is_const_type(operand.type);
        type = unqualify_type(operand.type);
        complete_type(type);
    }
    if (!is_aggregate_type(type)) {
        fatal_error(expr->pos, "Can only access fields on aggregates or pointers to aggregates");
        return operand_null;
    }
    for (size_t i = 0; i < type->aggregate.num_fields; i++) {
        TypeField field = type->aggregate.fields[i];
        if (field.name == expr->field.name) {
            Operand field_operand = operand.is_lvalue ? operand_lvalue(field.type) : operand_rvalue(field.type);
            if (was_const_type) {
                field_operand.type = type_const(field_operand.type);
            }
            return field_operand;
        }
    }
    fatal_error(expr->pos, "No field named '%s'", expr->field.name);
    return operand_null;
}