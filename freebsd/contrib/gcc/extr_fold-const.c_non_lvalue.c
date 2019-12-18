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
 int /*<<< orphan*/  NON_LVALUE_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ in_gimple_form ; 
 int /*<<< orphan*/  maybe_lvalue_p (int /*<<< orphan*/ ) ; 

tree
non_lvalue (tree x)
{
  /* While we are in GIMPLE, NON_LVALUE_EXPR doesn't mean anything to
     us.  */
  if (in_gimple_form)
    return x;

  if (! maybe_lvalue_p (x))
    return x;
  return build1 (NON_LVALUE_EXPR, TREE_TYPE (x), x);
}