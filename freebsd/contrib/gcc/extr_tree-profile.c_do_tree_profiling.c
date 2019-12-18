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

/* Variables and functions */
 scalar_t__ flag_branch_probabilities ; 
 scalar_t__ flag_test_coverage ; 
 scalar_t__ profile_arc_flag ; 
 int /*<<< orphan*/  tree_register_profile_hooks () ; 
 int /*<<< orphan*/  tree_register_value_prof_hooks () ; 

__attribute__((used)) static bool
do_tree_profiling (void)
{
  if (profile_arc_flag || flag_test_coverage || flag_branch_probabilities)
    {
      tree_register_profile_hooks ();
      tree_register_value_prof_hooks ();
      return true;
    }
  return false;
}