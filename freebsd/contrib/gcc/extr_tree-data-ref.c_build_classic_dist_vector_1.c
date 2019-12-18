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
struct subscript {int dummy; } ;
struct data_reference {int dummy; } ;
struct data_dependence_relation {int dummy; } ;
typedef  int* lambda_vector ;

/* Variables and functions */
 int /*<<< orphan*/  CHREC_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DDR_LOOP_NEST (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DDR_NB_LOOPS (struct data_dependence_relation*) ; 
 unsigned int DDR_NUM_SUBSCRIPTS (struct data_dependence_relation*) ; 
 struct subscript* DDR_SUBSCRIPT (struct data_dependence_relation*,unsigned int) ; 
 int /*<<< orphan*/  DR_ACCESS_FN (struct data_reference*,unsigned int) ; 
 int MIN (int,int) ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 int /*<<< orphan*/  SUB_DISTANCE (struct subscript*) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_contains_undetermined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_known ; 
 int /*<<< orphan*/  finalize_ddr_dependent (struct data_dependence_relation*,int /*<<< orphan*/ ) ; 
 int index_in_loop_nest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int int_cst_value (int /*<<< orphan*/ ) ; 
 int* lambda_vector_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  non_affine_dependence_relation (struct data_dependence_relation*) ; 

__attribute__((used)) static bool
build_classic_dist_vector_1 (struct data_dependence_relation *ddr,
			     struct data_reference *ddr_a,
			     struct data_reference *ddr_b,
			     lambda_vector dist_v, bool *init_b,
			     int *index_carry)
{
  unsigned i;
  lambda_vector init_v = lambda_vector_new (DDR_NB_LOOPS (ddr));

  for (i = 0; i < DDR_NUM_SUBSCRIPTS (ddr); i++)
    {
      tree access_fn_a, access_fn_b;
      struct subscript *subscript = DDR_SUBSCRIPT (ddr, i);

      if (chrec_contains_undetermined (SUB_DISTANCE (subscript)))
	{
	  non_affine_dependence_relation (ddr);
	  return false;
	}

      access_fn_a = DR_ACCESS_FN (ddr_a, i);
      access_fn_b = DR_ACCESS_FN (ddr_b, i);

      if (TREE_CODE (access_fn_a) == POLYNOMIAL_CHREC 
	  && TREE_CODE (access_fn_b) == POLYNOMIAL_CHREC)
	{
	  int dist, index;
	  int index_a = index_in_loop_nest (CHREC_VARIABLE (access_fn_a),
					    DDR_LOOP_NEST (ddr));
	  int index_b = index_in_loop_nest (CHREC_VARIABLE (access_fn_b),
					    DDR_LOOP_NEST (ddr));

	  /* The dependence is carried by the outermost loop.  Example:
	     | loop_1
	     |   A[{4, +, 1}_1]
	     |   loop_2
	     |     A[{5, +, 1}_2]
	     |   endloop_2
	     | endloop_1
	     In this case, the dependence is carried by loop_1.  */
	  index = index_a < index_b ? index_a : index_b;
	  *index_carry = MIN (index, *index_carry);

	  if (chrec_contains_undetermined (SUB_DISTANCE (subscript)))
	    {
	      non_affine_dependence_relation (ddr);
	      return false;
	    }
	  
	  dist = int_cst_value (SUB_DISTANCE (subscript));

	  /* This is the subscript coupling test.  If we have already
	     recorded a distance for this loop (a distance coming from
	     another subscript), it should be the same.  For example,
	     in the following code, there is no dependence:

	     | loop i = 0, N, 1
	     |   T[i+1][i] = ...
	     |   ... = T[i][i]
	     | endloop
	  */
	  if (init_v[index] != 0 && dist_v[index] != dist)
	    {
	      finalize_ddr_dependent (ddr, chrec_known);
	      return false;
	    }

	  dist_v[index] = dist;
	  init_v[index] = 1;
	  *init_b = true;
	}
      else
	{
	  /* This can be for example an affine vs. constant dependence
	     (T[i] vs. T[3]) that is not an affine dependence and is
	     not representable as a distance vector.  */
	  non_affine_dependence_relation (ddr);
	  return false;
	}
    }

  return true;
}