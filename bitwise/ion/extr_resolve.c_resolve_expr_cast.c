#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_8__ {int /*<<< orphan*/  expr; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {scalar_t__ kind; int /*<<< orphan*/  pos; TYPE_1__ cast; } ;
struct TYPE_9__ {int /*<<< orphan*/ * type; } ;
typedef  TYPE_2__ Operand ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 scalar_t__ EXPR_CAST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cast_operand (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_type_name (int /*<<< orphan*/ *) ; 
 TYPE_2__ resolve_expected_expr_rvalue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_typespec (int /*<<< orphan*/ ) ; 

Operand resolve_expr_cast(Expr *expr) {
    assert(expr->kind == EXPR_CAST);
    Type *type = resolve_typespec(expr->cast.type);
    Operand operand = resolve_expected_expr_rvalue(expr->cast.expr, type);
    if (!cast_operand(&operand, type)) {
        fatal_error(expr->pos, "Invalid type cast from %s to %s", get_type_name(operand.type), get_type_name(type));
    }
    return operand;
}