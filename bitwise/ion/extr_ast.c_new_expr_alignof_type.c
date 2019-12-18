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
typedef  int /*<<< orphan*/  Typespec ;
struct TYPE_4__ {int /*<<< orphan*/ * alignof_type; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_1__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_ALIGNOF_TYPE ; 
 TYPE_1__* new_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *new_expr_alignof_type(SrcPos pos, Typespec *type) {
    Expr *e = new_expr(EXPR_ALIGNOF_TYPE, pos);
    e->alignof_type = type;
    return e;
}