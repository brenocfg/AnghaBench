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
typedef  int /*<<< orphan*/  TokenMod ;
struct TYPE_5__ {unsigned long long val; int /*<<< orphan*/  suffix; int /*<<< orphan*/  mod; } ;
struct TYPE_6__ {TYPE_1__ int_lit; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_INT ; 
 TYPE_2__* new_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *new_expr_int(SrcPos pos, unsigned long long val, TokenMod mod, TokenSuffix suffix) {
    Expr *e = new_expr(EXPR_INT, pos);
    e->int_lit.val = val;
    e->int_lit.mod = mod;
    e->int_lit.suffix = suffix;
    return e;
}