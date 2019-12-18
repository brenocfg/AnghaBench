#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* arg; TYPE_2__* len; TYPE_2__* alloc; } ;
struct TYPE_9__ {TYPE_1__ new_expr; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_NEW ; 
 TYPE_2__* new_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *new_expr_new(SrcPos pos, Expr *alloc, Expr *len, Expr *arg) {
    Expr *e = new_expr(EXPR_NEW, pos);
    e->new_expr.alloc = alloc;
    e->new_expr.len = len;
    e->new_expr.arg = arg;
    return e;
}