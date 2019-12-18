#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  ExprKind ;
typedef  TYPE_1__ Expr ;

/* Variables and functions */
 TYPE_1__* ast_alloc (int) ; 

Expr *new_expr(ExprKind kind, SrcPos pos) {
    Expr *e = ast_alloc(sizeof(Expr));
    e->kind = kind;
    e->pos = pos;
    return e;
}