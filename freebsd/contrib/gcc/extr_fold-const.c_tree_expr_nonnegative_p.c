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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_STRICT_OVERFLOW_MISC ; 
 int /*<<< orphan*/  fold_overflow_warning (char*,int /*<<< orphan*/ ) ; 
 int tree_expr_nonnegative_warnv_p (int /*<<< orphan*/ ,int*) ; 

int
tree_expr_nonnegative_p (tree t)
{
  int ret;
  bool strict_overflow_p;

  strict_overflow_p = false;
  ret = tree_expr_nonnegative_warnv_p (t, &strict_overflow_p);
  if (strict_overflow_p)
    fold_overflow_warning (("assuming signed overflow does not occur when "
			    "determining that expression is always "
			    "non-negative"),
			   WARN_STRICT_OVERFLOW_MISC);
  return ret;
}