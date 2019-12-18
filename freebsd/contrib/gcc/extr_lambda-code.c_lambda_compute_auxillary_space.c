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
typedef  int* lambda_vector ;
typedef  int /*<<< orphan*/  lambda_trans_matrix ;
typedef  int** lambda_matrix ;
typedef  int /*<<< orphan*/  lambda_loopnest ;
typedef  int /*<<< orphan*/  lambda_loop ;
typedef  int /*<<< orphan*/ * lambda_linear_expression ;
typedef  int /*<<< orphan*/  lambda_lattice ;

/* Variables and functions */
 int** LATTICE_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LATTICE_ORIGIN (int /*<<< orphan*/ ) ; 
 int** LATTICE_ORIGIN_INVARIANTS (int /*<<< orphan*/ ) ; 
 int* LLE_COEFFICIENTS (int /*<<< orphan*/ *) ; 
 int LLE_CONSTANT (int /*<<< orphan*/ *) ; 
 int LLE_DENOMINATOR (int /*<<< orphan*/ *) ; 
 int* LLE_INVARIANT_COEFFICIENTS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LLE_NEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LL_LOWER_BOUND (int /*<<< orphan*/ ) ; 
 scalar_t__ LL_STEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LL_UPPER_BOUND (int /*<<< orphan*/ ) ; 
 int LN_DEPTH (int /*<<< orphan*/ ) ; 
 int LN_INVARIANTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LN_LOOPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LTM_MATRIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_nest_using_fourier_motzkin (int,int,int,int**,int**,int*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  lambda_lattice_compute_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lambda_matrix_add_mc (int**,int,int**,int,int**,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_inverse (int /*<<< orphan*/ ,int**,int) ; 
 int /*<<< orphan*/  lambda_matrix_mult (int**,int**,int**,int,int,int) ; 
 int** lambda_matrix_new (int,int) ; 
 int /*<<< orphan*/  lambda_matrix_vector_mult (int**,int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lambda_vector_add_mc (int*,int,int*,int,int*,int) ; 
 int* lambda_vector_new (int) ; 

__attribute__((used)) static lambda_loopnest
lambda_compute_auxillary_space (lambda_loopnest nest,
				lambda_trans_matrix trans)
{
  lambda_matrix A, B, A1, B1;
  lambda_vector a, a1;
  lambda_matrix invertedtrans;
  int depth, invariants, size;
  int i, j;
  lambda_loop loop;
  lambda_linear_expression expression;
  lambda_lattice lattice;

  depth = LN_DEPTH (nest);
  invariants = LN_INVARIANTS (nest);

  /* Unfortunately, we can't know the number of constraints we'll have
     ahead of time, but this should be enough even in ridiculous loop nest
     cases. We must not go over this limit.  */
  A = lambda_matrix_new (128, depth);
  B = lambda_matrix_new (128, invariants);
  a = lambda_vector_new (128);

  A1 = lambda_matrix_new (128, depth);
  B1 = lambda_matrix_new (128, invariants);
  a1 = lambda_vector_new (128);

  /* Store the bounds in the equation matrix A, constant vector a, and
     invariant matrix B, so that we have Ax <= a + B.
     This requires a little equation rearranging so that everything is on the
     correct side of the inequality.  */
  size = 0;
  for (i = 0; i < depth; i++)
    {
      loop = LN_LOOPS (nest)[i];

      /* First we do the lower bound.  */
      if (LL_STEP (loop) > 0)
	expression = LL_LOWER_BOUND (loop);
      else
	expression = LL_UPPER_BOUND (loop);

      for (; expression != NULL; expression = LLE_NEXT (expression))
	{
	  /* Fill in the coefficient.  */
	  for (j = 0; j < i; j++)
	    A[size][j] = LLE_COEFFICIENTS (expression)[j];

	  /* And the invariant coefficient.  */
	  for (j = 0; j < invariants; j++)
	    B[size][j] = LLE_INVARIANT_COEFFICIENTS (expression)[j];

	  /* And the constant.  */
	  a[size] = LLE_CONSTANT (expression);

	  /* Convert (2x+3y+2+b)/4 <= z to 2x+3y-4z <= -2-b.  IE put all
	     constants and single variables on   */
	  A[size][i] = -1 * LLE_DENOMINATOR (expression);
	  a[size] *= -1;
	  for (j = 0; j < invariants; j++)
	    B[size][j] *= -1;

	  size++;
	  /* Need to increase matrix sizes above.  */
	  gcc_assert (size <= 127);
	  
	}

      /* Then do the exact same thing for the upper bounds.  */
      if (LL_STEP (loop) > 0)
	expression = LL_UPPER_BOUND (loop);
      else
	expression = LL_LOWER_BOUND (loop);

      for (; expression != NULL; expression = LLE_NEXT (expression))
	{
	  /* Fill in the coefficient.  */
	  for (j = 0; j < i; j++)
	    A[size][j] = LLE_COEFFICIENTS (expression)[j];

	  /* And the invariant coefficient.  */
	  for (j = 0; j < invariants; j++)
	    B[size][j] = LLE_INVARIANT_COEFFICIENTS (expression)[j];

	  /* And the constant.  */
	  a[size] = LLE_CONSTANT (expression);

	  /* Convert z <= (2x+3y+2+b)/4 to -2x-3y+4z <= 2+b.  */
	  for (j = 0; j < i; j++)
	    A[size][j] *= -1;
	  A[size][i] = LLE_DENOMINATOR (expression);
	  size++;
	  /* Need to increase matrix sizes above.  */
	  gcc_assert (size <= 127);

	}
    }

  /* Compute the lattice base x = base * y + origin, where y is the
     base space.  */
  lattice = lambda_lattice_compute_base (nest);

  /* Ax <= a + B then becomes ALy <= a+B - A*origin.  L is the lattice base  */

  /* A1 = A * L */
  lambda_matrix_mult (A, LATTICE_BASE (lattice), A1, size, depth, depth);

  /* a1 = a - A * origin constant.  */
  lambda_matrix_vector_mult (A, size, depth, LATTICE_ORIGIN (lattice), a1);
  lambda_vector_add_mc (a, 1, a1, -1, a1, size);

  /* B1 = B - A * origin invariant.  */
  lambda_matrix_mult (A, LATTICE_ORIGIN_INVARIANTS (lattice), B1, size, depth,
		      invariants);
  lambda_matrix_add_mc (B, 1, B1, -1, B1, size, invariants);

  /* Now compute the auxiliary space bounds by first inverting U, multiplying
     it by A1, then performing Fourier-Motzkin.  */

  invertedtrans = lambda_matrix_new (depth, depth);

  /* Compute the inverse of U.  */
  lambda_matrix_inverse (LTM_MATRIX (trans),
			 invertedtrans, depth);

  /* A = A1 inv(U).  */
  lambda_matrix_mult (A1, invertedtrans, A, size, depth, depth);

  return compute_nest_using_fourier_motzkin (size, depth, invariants,
					     A, B1, a1);
}