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
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  CDI_POST_DOMINATORS ; 
 int /*<<< orphan*/  branch_prob () ; 
 scalar_t__ flag_branch_probabilities ; 
 scalar_t__ flag_profile_values ; 
 scalar_t__ flag_value_profile_transformations ; 
 int /*<<< orphan*/  free_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_profile_transformations () ; 

__attribute__((used)) static unsigned int
tree_profiling (void)
{
  branch_prob ();
  if (flag_branch_probabilities
      && flag_profile_values
      && flag_value_profile_transformations)
    value_profile_transformations ();
  /* The above could hose dominator info.  Currently there is
     none coming in, this is a safety valve.  It should be
     easy to adjust it, if and when there is some.  */
  free_dominance_info (CDI_DOMINATORS);
  free_dominance_info (CDI_POST_DOMINATORS);
  return 0;
}