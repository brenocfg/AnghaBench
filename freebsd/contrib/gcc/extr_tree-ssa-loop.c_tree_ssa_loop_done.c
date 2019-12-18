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
 int /*<<< orphan*/ * current_loops ; 
 int /*<<< orphan*/  free_numbers_of_iterations_estimates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop_optimizer_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scev_finalize () ; 

__attribute__((used)) static unsigned int
tree_ssa_loop_done (void)
{
  if (!current_loops)
    return 0;

  free_numbers_of_iterations_estimates (current_loops);
  scev_finalize ();
  loop_optimizer_finalize (current_loops);
  current_loops = NULL;
  return 0;
}