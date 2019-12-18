#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
typedef  int /*<<< orphan*/  Operand ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  operand_decay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_expected_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Operand resolve_expected_expr_rvalue(Expr *expr, Type *expected_type) {
    return operand_decay(resolve_expected_expr(expr, expected_type));
}