#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TokenSuffix ;
struct TYPE_5__ {char const* start; char const* end; double val; int /*<<< orphan*/  suffix; } ;
struct TYPE_6__ {TYPE_1__ float_lit; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_FLOAT ; 
 TYPE_2__* new_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *new_expr_float(SrcPos pos, const char *start, const char *end, double val, TokenSuffix suffix) {
    Expr *e = new_expr(EXPR_FLOAT, pos);
    e->float_lit.start = start;
    e->float_lit.end = end;
    e->float_lit.val = val;
    e->float_lit.suffix = suffix;
    return e;
}