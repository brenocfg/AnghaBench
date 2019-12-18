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
typedef  int /*<<< orphan*/  TokenKind ;
struct TYPE_7__ {TYPE_2__* right; TYPE_2__* left; int /*<<< orphan*/  op; } ;
struct TYPE_8__ {TYPE_1__ binary; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_BINARY ; 
 TYPE_2__* new_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *new_expr_binary(SrcPos pos, TokenKind op, Expr *left, Expr *right) {
    Expr *e = new_expr(EXPR_BINARY, pos);
    e->binary.op = op;
    e->binary.left = left;
    e->binary.right = right;
    return e;
}