#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct ivopts_data {int dummy; } ;
struct iv_use {int /*<<< orphan*/ ** op_p; } ;
struct iv_cand {int /*<<< orphan*/  iv; } ;
typedef  int /*<<< orphan*/ * bitmap ;
struct TYPE_2__ {int /*<<< orphan*/ * base; int /*<<< orphan*/  step; } ;

/* Variables and functions */
 unsigned int INFTY ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 struct ivopts_data* fd_ivopts_data ; 
 int /*<<< orphan*/  find_depends ; 
 unsigned int force_var_cost (struct ivopts_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 unsigned int get_computation_cost (struct ivopts_data*,struct iv_use*,struct iv_cand*,int,int /*<<< orphan*/ **) ; 
 TYPE_1__* get_iv (struct ivopts_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ may_eliminate_iv (struct ivopts_data*,struct iv_use*,struct iv_cand*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_use_iv_cost (struct ivopts_data*,struct iv_use*,struct iv_cand*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walk_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
determine_use_iv_cost_condition (struct ivopts_data *data,
				 struct iv_use *use, struct iv_cand *cand)
{
  tree bound = NULL_TREE, op, cond;
  bitmap depends_on = NULL;
  unsigned cost;

  /* Only consider real candidates.  */
  if (!cand->iv)
    {
      set_use_iv_cost (data, use, cand, INFTY, NULL, NULL_TREE);
      return false;
    }

  if (may_eliminate_iv (data, use, cand, &bound))
    {
      cost = force_var_cost (data, bound, &depends_on);

      set_use_iv_cost (data, use, cand, cost, depends_on, bound);
      return cost != INFTY;
    }

  /* The induction variable elimination failed; just express the original
     giv.  If it is compared with an invariant, note that we cannot get
     rid of it.  */
  cost = get_computation_cost (data, use, cand, false, &depends_on);

  cond = *use->op_p;
  if (TREE_CODE (cond) != SSA_NAME)
    {
      op = TREE_OPERAND (cond, 0);
      if (TREE_CODE (op) == SSA_NAME && !zero_p (get_iv (data, op)->step))
	op = TREE_OPERAND (cond, 1);
      if (TREE_CODE (op) == SSA_NAME)
	{
	  op = get_iv (data, op)->base;
	  fd_ivopts_data = data;
	  walk_tree (&op, find_depends, &depends_on, NULL);
	}
    }

  set_use_iv_cost (data, use, cand, cost, depends_on, NULL);
  return cost != INFTY;
}