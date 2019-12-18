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
typedef  int /*<<< orphan*/  lambda_vector ;
typedef  int /*<<< orphan*/  DDR_ARE_DEPENDENT ;

/* Variables and functions */
 int /*<<< orphan*/  CHREC_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DDR_A (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DDR_LOOP_NEST (struct data_dependence_relation*) ; 
 int DDR_NB_LOOPS (struct data_dependence_relation*) ; 
 int DDR_NUM_SUBSCRIPTS (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DR_ACCESS_FN (int /*<<< orphan*/ ,unsigned int) ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_multivariate_self_dist (struct data_dependence_relation*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_outer_distances (struct data_dependence_relation*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  evolution_function_is_univariate_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_in_loop_nest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lambda_vector_new (int) ; 

__attribute__((used)) static void
add_other_self_distances (struct data_dependence_relation *ddr)
{
  lambda_vector dist_v;
  unsigned i;
  int index_carry = DDR_NB_LOOPS (ddr);

  for (i = 0; i < DDR_NUM_SUBSCRIPTS (ddr); i++)
    {
      tree access_fun = DR_ACCESS_FN (DDR_A (ddr), i);

      if (TREE_CODE (access_fun) == POLYNOMIAL_CHREC)
	{
	  if (!evolution_function_is_univariate_p (access_fun))
	    {
	      if (DDR_NUM_SUBSCRIPTS (ddr) != 1)
		{
		  DDR_ARE_DEPENDENT (ddr) = chrec_dont_know;
		  return;
		}

	      add_multivariate_self_dist (ddr, DR_ACCESS_FN (DDR_A (ddr), 0));
	      return;
	    }

	  index_carry = MIN (index_carry,
			     index_in_loop_nest (CHREC_VARIABLE (access_fun),
						 DDR_LOOP_NEST (ddr)));
	}
    }

  dist_v = lambda_vector_new (DDR_NB_LOOPS (ddr));
  add_outer_distances (ddr, dist_v, index_carry);
}