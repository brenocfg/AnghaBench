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
struct nb_iter_bound {int /*<<< orphan*/  at_stmt; scalar_t__ bound; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int GE_EXPR ; 
 int GT_EXPR ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (scalar_t__) ; 
 scalar_t__ TYPE_UNSIGNED (scalar_t__) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 scalar_t__ fold_binary (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ is_gimple_min_invariant (scalar_t__) ; 
 int nonzero_p (scalar_t__) ; 
 scalar_t__ stmt_dominates_stmt_p (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
n_of_executions_at_most (tree stmt,
			 struct nb_iter_bound *niter_bound, 
			 tree niter)
{
  tree cond;
  tree bound = niter_bound->bound;
  tree bound_type = TREE_TYPE (bound);
  tree nit_type = TREE_TYPE (niter);
  enum tree_code cmp;

  gcc_assert (TYPE_UNSIGNED (bound_type)
	      && TYPE_UNSIGNED (nit_type)
	      && is_gimple_min_invariant (bound));
  if (TYPE_PRECISION (nit_type) > TYPE_PRECISION (bound_type))
    bound = fold_convert (nit_type, bound);
  else
    niter = fold_convert (bound_type, niter);

  /* After the statement niter_bound->at_stmt we know that anything is
     executed at most BOUND times.  */
  if (stmt && stmt_dominates_stmt_p (niter_bound->at_stmt, stmt))
    cmp = GE_EXPR;
  /* Before the statement niter_bound->at_stmt we know that anything
     is executed at most BOUND + 1 times.  */
  else
    cmp = GT_EXPR;

  cond = fold_binary (cmp, boolean_type_node, niter, bound);
  return nonzero_p (cond);
}