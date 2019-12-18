#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TokenKind ;
struct TYPE_4__ {int /*<<< orphan*/  right; int /*<<< orphan*/  left; int /*<<< orphan*/  op; } ;
struct TYPE_5__ {scalar_t__ kind; TYPE_1__ binary; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  Operand ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 scalar_t__ EXPR_BINARY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  resolve_expr_binary_op (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_expr_rvalue (int /*<<< orphan*/ ) ; 
 char* token_kind_name (int /*<<< orphan*/ ) ; 

Operand resolve_expr_binary(Expr *expr) {
    assert(expr->kind == EXPR_BINARY);
    Operand left = resolve_expr_rvalue(expr->binary.left);
    Operand right = resolve_expr_rvalue(expr->binary.right);
    TokenKind op = expr->binary.op;
    const char *op_name = token_kind_name(op);
    return resolve_expr_binary_op(op, op_name, expr->pos, left, right, expr->binary.left, expr->binary.right);
}