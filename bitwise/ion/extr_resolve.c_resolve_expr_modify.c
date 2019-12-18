#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ kind; scalar_t__ nonmodifiable; } ;
typedef  TYPE_2__ Type ;
struct TYPE_12__ {int /*<<< orphan*/  op; int /*<<< orphan*/  expr; } ;
struct TYPE_15__ {TYPE_1__ modify; int /*<<< orphan*/  pos; } ;
struct TYPE_14__ {int /*<<< orphan*/  is_lvalue; TYPE_2__* type; } ;
typedef  TYPE_3__ Operand ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 scalar_t__ TYPE_PTR ; 
 int /*<<< orphan*/  complete_type (TYPE_2__*) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ is_integer_type (TYPE_2__*) ; 
 TYPE_3__ operand_rvalue (TYPE_2__*) ; 
 TYPE_3__ resolve_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  token_kind_name (int /*<<< orphan*/ ) ; 

Operand resolve_expr_modify(Expr *expr) {
    Operand operand = resolve_expr(expr->modify.expr);
    Type *type = operand.type;
    complete_type(type);
    if (!operand.is_lvalue) {
        fatal_error(expr->pos, "Cannot modify non-lvalue");
    }
    if (type->nonmodifiable) {
        fatal_error(expr->pos, "Cannot modify non-modifiable type");
    }
    if (!(is_integer_type(type) || type->kind == TYPE_PTR)) {
        fatal_error(expr->pos, "%s only valid for integer and pointer types", token_kind_name(expr->modify.op));
    }
    return operand_rvalue(type);
}