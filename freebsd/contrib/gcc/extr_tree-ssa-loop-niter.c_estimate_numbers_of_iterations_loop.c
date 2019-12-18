#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct tree_niter_desc {int /*<<< orphan*/  additional_info; int /*<<< orphan*/  may_be_zero; int /*<<< orphan*/  niter; } ;
struct loop {scalar_t__ estimated_nb_iterations; } ;
typedef  TYPE_1__* edge ;
struct TYPE_5__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  COND_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_contains_undetermined (scalar_t__) ; 
 scalar_t__ chrec_dont_know ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 TYPE_1__** get_loop_exit_edges (struct loop*,unsigned int*) ; 
 int /*<<< orphan*/  infer_loop_bounds_from_undefined (struct loop*) ; 
 int /*<<< orphan*/  last_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonzero_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  number_of_iterations_exit (struct loop*,TYPE_1__*,struct tree_niter_desc*,int) ; 
 int /*<<< orphan*/  record_estimate (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
estimate_numbers_of_iterations_loop (struct loop *loop)
{
  edge *exits;
  tree niter, type;
  unsigned i, n_exits;
  struct tree_niter_desc niter_desc;

  /* Give up if we already have tried to compute an estimation.  */
  if (loop->estimated_nb_iterations == chrec_dont_know
      /* Or when we already have an estimation.  */
      || (loop->estimated_nb_iterations != NULL_TREE
	  && TREE_CODE (loop->estimated_nb_iterations) == INTEGER_CST))
    return;
  else
    loop->estimated_nb_iterations = chrec_dont_know;

  exits = get_loop_exit_edges (loop, &n_exits);
  for (i = 0; i < n_exits; i++)
    {
      if (!number_of_iterations_exit (loop, exits[i], &niter_desc, false))
	continue;

      niter = niter_desc.niter;
      type = TREE_TYPE (niter);
      if (!zero_p (niter_desc.may_be_zero)
	  && !nonzero_p (niter_desc.may_be_zero))
	niter = build3 (COND_EXPR, type, niter_desc.may_be_zero,
			build_int_cst (type, 0),
			niter);
      record_estimate (loop, niter,
		       niter_desc.additional_info,
		       last_stmt (exits[i]->src));
    }
  free (exits);
  
  if (chrec_contains_undetermined (loop->estimated_nb_iterations))
    infer_loop_bounds_from_undefined (loop);
}