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
struct data_dependence_relation {int dummy; } ;
typedef  int /*<<< orphan*/ * lambda_vector ;
typedef  int /*<<< orphan*/  DDR_ARE_DEPENDENT ;

/* Variables and functions */
 int /*<<< orphan*/  CHREC_LEFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_RIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DDR_LOOP_NEST (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DDR_NB_LOOPS (struct data_dependence_relation*) ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_outer_distances (struct data_dependence_relation*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int index_in_loop_nest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_cst_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lambda_vector_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_dist_v (struct data_dependence_relation*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_multivariate_self_dist (struct data_dependence_relation *ddr, tree c_2)
{
  int x_1, x_2;
  tree c_1 = CHREC_LEFT (c_2);
  tree c_0 = CHREC_LEFT (c_1);
  lambda_vector dist_v;

  /* Polynomials with more than 2 variables are not handled yet.  */
  if (TREE_CODE (c_0) != INTEGER_CST)
    {
      DDR_ARE_DEPENDENT (ddr) = chrec_dont_know;
      return;
    }

  x_2 = index_in_loop_nest (CHREC_VARIABLE (c_2), DDR_LOOP_NEST (ddr));
  x_1 = index_in_loop_nest (CHREC_VARIABLE (c_1), DDR_LOOP_NEST (ddr));

  /* For "{{0, +, 2}_1, +, 3}_2" the distance vector is (3, -2).  */
  dist_v = lambda_vector_new (DDR_NB_LOOPS (ddr));
  dist_v[x_1] = int_cst_value (CHREC_RIGHT (c_2));
  dist_v[x_2] = -int_cst_value (CHREC_RIGHT (c_1));
  save_dist_v (ddr, dist_v);

  add_outer_distances (ddr, dist_v, x_1);
}