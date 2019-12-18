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
struct loop {scalar_t__ depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHI_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analyze_evolution_in_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analyze_initial_condition (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analyze_scalar_evolution (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_overall_effect_of_inner_loop (struct loop*,int /*<<< orphan*/ ) ; 
 struct loop* loop_containing_stmt (int /*<<< orphan*/ ) ; 
 struct loop* superloop_at_depth (struct loop*,scalar_t__) ; 

__attribute__((used)) static tree 
interpret_loop_phi (struct loop *loop, tree loop_phi_node)
{
  tree res;
  struct loop *phi_loop = loop_containing_stmt (loop_phi_node);
  tree init_cond;
  
  if (phi_loop != loop)
    {
      struct loop *subloop;
      tree evolution_fn = analyze_scalar_evolution
	(phi_loop, PHI_RESULT (loop_phi_node));

      /* Dive one level deeper.  */
      subloop = superloop_at_depth (phi_loop, loop->depth + 1);

      /* Interpret the subloop.  */
      res = compute_overall_effect_of_inner_loop (subloop, evolution_fn);
      return res;
    }

  /* Otherwise really interpret the loop phi.  */
  init_cond = analyze_initial_condition (loop_phi_node);
  res = analyze_evolution_in_loop (loop_phi_node, init_cond);

  return res;
}