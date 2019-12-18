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
typedef  int** lambda_matrix ;
typedef  int /*<<< orphan*/  lambda_loopnest ;
typedef  int lambda_loop ;
typedef  int /*<<< orphan*/  lambda_linear_expression ;
typedef  int /*<<< orphan*/  lambda_lattice ;

/* Variables and functions */
 int** LATTICE_BASE (int /*<<< orphan*/ ) ; 
 scalar_t__* LATTICE_ORIGIN (int /*<<< orphan*/ ) ; 
 scalar_t__** LATTICE_ORIGIN_INVARIANTS (int /*<<< orphan*/ ) ; 
 int* LLE_COEFFICIENTS (int /*<<< orphan*/ ) ; 
 scalar_t__ LLE_CONSTANT (int /*<<< orphan*/ ) ; 
 int LLE_DENOMINATOR (int /*<<< orphan*/ ) ; 
 scalar_t__* LLE_INVARIANT_COEFFICIENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLE_NEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LL_LOWER_BOUND (int) ; 
 int LL_STEP (int) ; 
 int LN_DEPTH (int /*<<< orphan*/ ) ; 
 int LN_INVARIANTS (int /*<<< orphan*/ ) ; 
 int* LN_LOOPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  lambda_lattice_new (int,int) ; 

__attribute__((used)) static lambda_lattice
lambda_lattice_compute_base (lambda_loopnest nest)
{
  lambda_lattice ret;
  int depth, invariants;
  lambda_matrix base;

  int i, j, step;
  lambda_loop loop;
  lambda_linear_expression expression;

  depth = LN_DEPTH (nest);
  invariants = LN_INVARIANTS (nest);

  ret = lambda_lattice_new (depth, invariants);
  base = LATTICE_BASE (ret);
  for (i = 0; i < depth; i++)
    {
      loop = LN_LOOPS (nest)[i];
      gcc_assert (loop);
      step = LL_STEP (loop);
      /* If we have a step of 1, then the base is one, and the
         origin and invariant coefficients are 0.  */
      if (step == 1)
	{
	  for (j = 0; j < depth; j++)
	    base[i][j] = 0;
	  base[i][i] = 1;
	  LATTICE_ORIGIN (ret)[i] = 0;
	  for (j = 0; j < invariants; j++)
	    LATTICE_ORIGIN_INVARIANTS (ret)[i][j] = 0;
	}
      else
	{
	  /* Otherwise, we need the lower bound expression (which must
	     be an affine function)  to determine the base.  */
	  expression = LL_LOWER_BOUND (loop);
	  gcc_assert (expression && !LLE_NEXT (expression) 
		      && LLE_DENOMINATOR (expression) == 1);

	  /* The lower triangular portion of the base is going to be the
	     coefficient times the step */
	  for (j = 0; j < i; j++)
	    base[i][j] = LLE_COEFFICIENTS (expression)[j]
	      * LL_STEP (LN_LOOPS (nest)[j]);
	  base[i][i] = step;
	  for (j = i + 1; j < depth; j++)
	    base[i][j] = 0;

	  /* Origin for this loop is the constant of the lower bound
	     expression.  */
	  LATTICE_ORIGIN (ret)[i] = LLE_CONSTANT (expression);

	  /* Coefficient for the invariants are equal to the invariant
	     coefficients in the expression.  */
	  for (j = 0; j < invariants; j++)
	    LATTICE_ORIGIN_INVARIANTS (ret)[i][j] =
	      LLE_INVARIANT_COEFFICIENTS (expression)[j];
	}
    }
  return ret;
}