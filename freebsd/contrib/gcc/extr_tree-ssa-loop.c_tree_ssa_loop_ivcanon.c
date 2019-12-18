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
 unsigned int canonicalize_induction_variables (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_loops ; 

__attribute__((used)) static unsigned int
tree_ssa_loop_ivcanon (void)
{
  if (!current_loops)
    return 0;

  return canonicalize_induction_variables (current_loops);
}