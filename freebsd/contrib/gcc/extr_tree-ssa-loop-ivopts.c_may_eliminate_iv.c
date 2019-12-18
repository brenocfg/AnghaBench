#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct loop {int /*<<< orphan*/  latch; } ;
struct ivopts_data {struct loop* current_loop; } ;
struct iv_use {scalar_t__ stmt; } ;
struct iv_cand {TYPE_3__* iv; } ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_6__ {scalar_t__ step; } ;
struct TYPE_5__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 scalar_t__ COND_EXPR ; 
 TYPE_1__* EDGE_SUCC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GE_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bb_for_stmt (scalar_t__) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  cand_value_at (struct loop*,struct iv_cand*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dominated_by_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flow_bb_inside_loop_p (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_affine_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_nonzerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_period (TYPE_3__*) ; 
 scalar_t__ last_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niter_for_exit (struct ivopts_data*,TYPE_1__*) ; 

__attribute__((used)) static bool
may_eliminate_iv (struct ivopts_data *data,
		  struct iv_use *use, struct iv_cand *cand, tree *bound)
{
  basic_block ex_bb;
  edge exit;
  tree nit, nit_type;
  tree wider_type, period, per_type;
  struct loop *loop = data->current_loop;
  
  if (TREE_CODE (cand->iv->step) != INTEGER_CST)
    return false;

  /* For now works only for exits that dominate the loop latch.  TODO -- extend
     for other conditions inside loop body.  */
  ex_bb = bb_for_stmt (use->stmt);
  if (use->stmt != last_stmt (ex_bb)
      || TREE_CODE (use->stmt) != COND_EXPR)
    return false;
  if (!dominated_by_p (CDI_DOMINATORS, loop->latch, ex_bb))
    return false;

  exit = EDGE_SUCC (ex_bb, 0);
  if (flow_bb_inside_loop_p (loop, exit->dest))
    exit = EDGE_SUCC (ex_bb, 1);
  if (flow_bb_inside_loop_p (loop, exit->dest))
    return false;

  nit = niter_for_exit (data, exit);
  if (!nit)
    return false;

  nit_type = TREE_TYPE (nit);

  /* Determine whether we may use the variable to test whether niter iterations
     elapsed.  This is the case iff the period of the induction variable is
     greater than the number of iterations.  */
  period = iv_period (cand->iv);
  if (!period)
    return false;
  per_type = TREE_TYPE (period);

  wider_type = TREE_TYPE (period);
  if (TYPE_PRECISION (nit_type) < TYPE_PRECISION (per_type))
    wider_type = per_type;
  else
    wider_type = nit_type;

  if (!integer_nonzerop (fold_build2 (GE_EXPR, boolean_type_node,
				      fold_convert (wider_type, period),
				      fold_convert (wider_type, nit))))
    return false;

  *bound = fold_affine_expr (cand_value_at (loop, cand, use->stmt, nit));
  return true;
}