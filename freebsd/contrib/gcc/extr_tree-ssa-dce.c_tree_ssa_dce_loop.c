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
 int /*<<< orphan*/  current_loops ; 
 int /*<<< orphan*/  free_numbers_of_iterations_estimates (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perform_tree_ssa_dce (int) ; 
 int /*<<< orphan*/  scev_reset () ; 

__attribute__((used)) static unsigned int
tree_ssa_dce_loop (void)
{
  perform_tree_ssa_dce (/*aggressive=*/false);
  free_numbers_of_iterations_estimates (current_loops);
  scev_reset ();
  return 0;
}