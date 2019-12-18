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
 int TDF_STATS ; 
 int VEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VEC_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  analyze_scalar_evolution_for_all_loop_phi_nodes (int*) ; 
 int /*<<< orphan*/  current_loops ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int exit_conditions ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  number_of_iterations_for_all_loops (int*) ; 
 int /*<<< orphan*/  select_loops_exit_conditions (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tree ; 

void
scev_analysis (void)
{
  VEC(tree,heap) *exit_conditions;
  
  exit_conditions = VEC_alloc (tree, heap, 37);
  select_loops_exit_conditions (current_loops, &exit_conditions);

  if (dump_file && (dump_flags & TDF_STATS))
    analyze_scalar_evolution_for_all_loop_phi_nodes (&exit_conditions);
  
  number_of_iterations_for_all_loops (&exit_conditions);
  VEC_free (tree, heap, exit_conditions);
}