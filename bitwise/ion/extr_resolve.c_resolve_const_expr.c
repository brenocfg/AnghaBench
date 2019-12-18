#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pos; } ;
struct TYPE_7__ {int /*<<< orphan*/  is_const; } ;
typedef  TYPE_1__ Operand ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ resolve_expr (TYPE_2__*) ; 

Operand resolve_const_expr(Expr *expr) {
    Operand operand = resolve_expr(expr);
    if (!operand.is_const) {
        fatal_error(expr->pos, "Expected constant expression");
    }
    return operand;
}