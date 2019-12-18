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
struct ivopts_data {int /*<<< orphan*/  current_loop; } ;
struct iv_cand {int /*<<< orphan*/  var_after; int /*<<< orphan*/  var_before; } ;
struct iv {int /*<<< orphan*/  ssa_name; int /*<<< orphan*/  step; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_ORIGINAL ; 
 int /*<<< orphan*/  PHI_ARG_DEF_FROM_EDGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PHI_NODE ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_candidate (struct ivopts_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct iv_cand* add_candidate_1 (struct ivopts_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_latch_edge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_old_iv_candidates (struct ivopts_data *data, struct iv *iv)
{
  tree phi, def;
  struct iv_cand *cand;

  add_candidate (data, iv->base, iv->step, true, NULL);

  /* The same, but with initial value zero.  */
  add_candidate (data,
		 build_int_cst (TREE_TYPE (iv->base), 0),
		 iv->step, true, NULL);

  phi = SSA_NAME_DEF_STMT (iv->ssa_name);
  if (TREE_CODE (phi) == PHI_NODE)
    {
      /* Additionally record the possibility of leaving the original iv
	 untouched.  */
      def = PHI_ARG_DEF_FROM_EDGE (phi, loop_latch_edge (data->current_loop));
      cand = add_candidate_1 (data,
			      iv->base, iv->step, true, IP_ORIGINAL, NULL,
			      SSA_NAME_DEF_STMT (def));
      cand->var_before = iv->ssa_name;
      cand->var_after = def;
    }
}