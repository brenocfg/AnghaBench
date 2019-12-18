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

/* Variables and functions */
 int FLOOR_DIV (int,int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_polynomial_chrec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gcd (int,int) ; 
 int /*<<< orphan*/  integer_zero_node ; 

__attribute__((used)) static void
compute_overlap_steps_for_affine_univar (int niter, int step_a, int step_b, 
					 tree *overlaps_a, tree *overlaps_b, 
					 tree *last_conflicts, int dim)
{
  if (((step_a > 0 && step_b > 0)
       || (step_a < 0 && step_b < 0)))
    {
      int step_overlaps_a, step_overlaps_b;
      int gcd_steps_a_b, last_conflict, tau2;

      gcd_steps_a_b = gcd (step_a, step_b);
      step_overlaps_a = step_b / gcd_steps_a_b;
      step_overlaps_b = step_a / gcd_steps_a_b;

      tau2 = FLOOR_DIV (niter, step_overlaps_a);
      tau2 = MIN (tau2, FLOOR_DIV (niter, step_overlaps_b));
      last_conflict = tau2;

      *overlaps_a = build_polynomial_chrec
	(dim, integer_zero_node,
	 build_int_cst (NULL_TREE, step_overlaps_a));
      *overlaps_b = build_polynomial_chrec
	(dim, integer_zero_node,
	 build_int_cst (NULL_TREE, step_overlaps_b));
      *last_conflicts = build_int_cst (NULL_TREE, last_conflict);
    }

  else
    {
      *overlaps_a = integer_zero_node;
      *overlaps_b = integer_zero_node;
      *last_conflicts = integer_zero_node;
    }
}