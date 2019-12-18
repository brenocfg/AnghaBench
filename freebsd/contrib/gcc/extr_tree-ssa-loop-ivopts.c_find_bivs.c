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
typedef  scalar_t__ tree ;
struct loop {int /*<<< orphan*/  header; } ;
struct ivopts_data {struct loop* current_loop; } ;

/* Variables and functions */
 scalar_t__ PHI_ARG_DEF_FROM_EDGE (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  PHI_RESULT (scalar_t__) ; 
 scalar_t__ SSA_NAME_OCCURS_IN_ABNORMAL_PHI (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ contains_abnormal_ssa_name_p (scalar_t__) ; 
 scalar_t__ determine_biv_step (scalar_t__) ; 
 scalar_t__ expand_simple_operations (scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  loop_preheader_edge (struct loop*) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_iv (struct ivopts_data*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
find_bivs (struct ivopts_data *data)
{
  tree phi, step, type, base;
  bool found = false;
  struct loop *loop = data->current_loop;

  for (phi = phi_nodes (loop->header); phi; phi = PHI_CHAIN (phi))
    {
      if (SSA_NAME_OCCURS_IN_ABNORMAL_PHI (PHI_RESULT (phi)))
	continue;

      step = determine_biv_step (phi);
      if (!step)
	continue;

      base = PHI_ARG_DEF_FROM_EDGE (phi, loop_preheader_edge (loop));
      base = expand_simple_operations (base);
      if (contains_abnormal_ssa_name_p (base)
	  || contains_abnormal_ssa_name_p (step))
	continue;

      type = TREE_TYPE (PHI_RESULT (phi));
      base = fold_convert (type, base);
      if (step)
	step = fold_convert (type, step);

      set_iv (data, PHI_RESULT (phi), base, step);
      found = true;
    }

  return found;
}