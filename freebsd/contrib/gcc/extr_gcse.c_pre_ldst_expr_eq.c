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
struct ls_expr {int /*<<< orphan*/  pattern; } ;

/* Variables and functions */
 int expr_equiv_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pre_ldst_expr_eq (const void *p1, const void *p2)
{
  const struct ls_expr *ptr1 = p1, *ptr2 = p2;
  return expr_equiv_p (ptr1->pattern, ptr2->pattern);
}