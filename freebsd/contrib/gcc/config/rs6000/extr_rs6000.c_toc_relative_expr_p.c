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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ constant_pool_expr_1 (int /*<<< orphan*/ ,int*,int*) ; 

bool
toc_relative_expr_p (rtx op)
{
  int have_sym = 0;
  int have_toc = 0;
  return constant_pool_expr_1 (op, &have_sym, &have_toc) && have_toc;
}