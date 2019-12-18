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
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_really_no_inline ; 
 int /*<<< orphan*/ * lookup_attribute (char*,int /*<<< orphan*/ ) ; 

int
lhd_tree_inlining_cannot_inline_tree_fn (tree *fnp)
{
  if (flag_really_no_inline
      && lookup_attribute ("always_inline", DECL_ATTRIBUTES (*fnp)) == NULL)
    return 1;

  return 0;
}