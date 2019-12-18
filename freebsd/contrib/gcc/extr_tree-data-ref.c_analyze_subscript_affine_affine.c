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
typedef  int** lambda_matrix ;

/* Variables and functions */
 int CEIL (int,int) ; 
 scalar_t__ CHREC_RIGHT (scalar_t__) ; 
 int /*<<< orphan*/  CHREC_VARIABLE (scalar_t__) ; 
 int FLOOR_DIV (int,int) ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 scalar_t__ NULL_TREE ; 
 int TDF_DETAILS ; 
 scalar_t__ build_int_cst (scalar_t__,int) ; 
 scalar_t__ build_polynomial_chrec (int,scalar_t__,scalar_t__) ; 
 scalar_t__ chrec_dont_know ; 
 scalar_t__ chrec_known ; 
 int /*<<< orphan*/  compute_overlap_steps_for_affine_1_2 (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  compute_overlap_steps_for_affine_univar (int,int,int,scalar_t__*,scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 scalar_t__ eq_evolutions_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 scalar_t__ get_number_of_iters_for_loop (int /*<<< orphan*/ ) ; 
 int initialize_matrix_A (int**,scalar_t__,unsigned int,int) ; 
 int int_cst_value (scalar_t__) ; 
 int /*<<< orphan*/  int_divides_p (int,int) ; 
 scalar_t__ integer_zero_node ; 
 int** lambda_matrix_new (unsigned int,int) ; 
 int /*<<< orphan*/  lambda_matrix_right_hermite (int**,unsigned int,int,int**,int**) ; 
 int /*<<< orphan*/  lambda_matrix_row_negate (int**,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int nb_vars_in_chrec (scalar_t__) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
analyze_subscript_affine_affine (tree chrec_a, 
				 tree chrec_b,
				 tree *overlaps_a, 
				 tree *overlaps_b, 
				 tree *last_conflicts)
{
  unsigned nb_vars_a, nb_vars_b, dim;
  int init_a, init_b, gamma, gcd_alpha_beta;
  int tau1, tau2;
  lambda_matrix A, U, S;

  if (eq_evolutions_p (chrec_a, chrec_b))
    {
      /* The accessed index overlaps for each iteration in the
	 loop.  */
      *overlaps_a = integer_zero_node;
      *overlaps_b = integer_zero_node;
      *last_conflicts = chrec_dont_know;
      return;
    }
  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "(analyze_subscript_affine_affine \n");
  
  /* For determining the initial intersection, we have to solve a
     Diophantine equation.  This is the most time consuming part.
     
     For answering to the question: "Is there a dependence?" we have
     to prove that there exists a solution to the Diophantine
     equation, and that the solution is in the iteration domain,
     i.e. the solution is positive or zero, and that the solution
     happens before the upper bound loop.nb_iterations.  Otherwise
     there is no dependence.  This function outputs a description of
     the iterations that hold the intersections.  */

  nb_vars_a = nb_vars_in_chrec (chrec_a);
  nb_vars_b = nb_vars_in_chrec (chrec_b);

  dim = nb_vars_a + nb_vars_b;
  U = lambda_matrix_new (dim, dim);
  A = lambda_matrix_new (dim, 1);
  S = lambda_matrix_new (dim, 1);

  init_a = initialize_matrix_A (A, chrec_a, 0, 1);
  init_b = initialize_matrix_A (A, chrec_b, nb_vars_a, -1);
  gamma = init_b - init_a;

  /* Don't do all the hard work of solving the Diophantine equation
     when we already know the solution: for example, 
     | {3, +, 1}_1
     | {3, +, 4}_2
     | gamma = 3 - 3 = 0.
     Then the first overlap occurs during the first iterations: 
     | {3, +, 1}_1 ({0, +, 4}_x) = {3, +, 4}_2 ({0, +, 1}_x)
  */
  if (gamma == 0)
    {
      if (nb_vars_a == 1 && nb_vars_b == 1)
	{
	  int step_a, step_b;
	  int niter, niter_a, niter_b;
	  tree numiter_a, numiter_b;

	  numiter_a = get_number_of_iters_for_loop (CHREC_VARIABLE (chrec_a));
	  numiter_b = get_number_of_iters_for_loop (CHREC_VARIABLE (chrec_b));
	  if (numiter_a == NULL_TREE || numiter_b == NULL_TREE)
	    {
	      if (dump_file && (dump_flags & TDF_DETAILS))
		fprintf (dump_file, "affine-affine test failed: missing iteration counts.\n");
	      *overlaps_a = chrec_dont_know;
	      *overlaps_b = chrec_dont_know;
	      *last_conflicts = chrec_dont_know;
	      goto end_analyze_subs_aa;
	    }

	  niter_a = int_cst_value (numiter_a);
	  niter_b = int_cst_value (numiter_b);
	  niter = MIN (niter_a, niter_b);

	  step_a = int_cst_value (CHREC_RIGHT (chrec_a));
	  step_b = int_cst_value (CHREC_RIGHT (chrec_b));

	  compute_overlap_steps_for_affine_univar (niter, step_a, step_b, 
						   overlaps_a, overlaps_b, 
						   last_conflicts, 1);
	}

      else if (nb_vars_a == 2 && nb_vars_b == 1)
	compute_overlap_steps_for_affine_1_2
	  (chrec_a, chrec_b, overlaps_a, overlaps_b, last_conflicts);

      else if (nb_vars_a == 1 && nb_vars_b == 2)
	compute_overlap_steps_for_affine_1_2
	  (chrec_b, chrec_a, overlaps_b, overlaps_a, last_conflicts);

      else
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "affine-affine test failed: too many variables.\n");
	  *overlaps_a = chrec_dont_know;
	  *overlaps_b = chrec_dont_know;
	  *last_conflicts = chrec_dont_know;
	}
      goto end_analyze_subs_aa;
    }

  /* U.A = S */
  lambda_matrix_right_hermite (A, dim, 1, S, U);

  if (S[0][0] < 0)
    {
      S[0][0] *= -1;
      lambda_matrix_row_negate (U, dim, 0);
    }
  gcd_alpha_beta = S[0][0];

  /* Something went wrong: for example in {1, +, 0}_5 vs. {0, +, 0}_5,
     but that is a quite strange case.  Instead of ICEing, answer
     don't know.  */
  if (gcd_alpha_beta == 0)
    {
      *overlaps_a = chrec_dont_know;
      *overlaps_b = chrec_dont_know;
      *last_conflicts = chrec_dont_know;
      goto end_analyze_subs_aa;
    }

  /* The classic "gcd-test".  */
  if (!int_divides_p (gcd_alpha_beta, gamma))
    {
      /* The "gcd-test" has determined that there is no integer
	 solution, i.e. there is no dependence.  */
      *overlaps_a = chrec_known;
      *overlaps_b = chrec_known;
      *last_conflicts = integer_zero_node;
    }

  /* Both access functions are univariate.  This includes SIV and MIV cases.  */
  else if (nb_vars_a == 1 && nb_vars_b == 1)
    {
      /* Both functions should have the same evolution sign.  */
      if (((A[0][0] > 0 && -A[1][0] > 0)
	   || (A[0][0] < 0 && -A[1][0] < 0)))
	{
	  /* The solutions are given by:
	     | 
	     | [GAMMA/GCD_ALPHA_BETA  t].[u11 u12]  = [x0]
	     |                           [u21 u22]    [y0]
	 
	     For a given integer t.  Using the following variables,
	 
	     | i0 = u11 * gamma / gcd_alpha_beta
	     | j0 = u12 * gamma / gcd_alpha_beta
	     | i1 = u21
	     | j1 = u22
	 
	     the solutions are:
	 
	     | x0 = i0 + i1 * t, 
	     | y0 = j0 + j1 * t.  */
      
	  int i0, j0, i1, j1;

	  /* X0 and Y0 are the first iterations for which there is a
	     dependence.  X0, Y0 are two solutions of the Diophantine
	     equation: chrec_a (X0) = chrec_b (Y0).  */
	  int x0, y0;
	  int niter, niter_a, niter_b;
	  tree numiter_a, numiter_b;

	  numiter_a = get_number_of_iters_for_loop (CHREC_VARIABLE (chrec_a));
	  numiter_b = get_number_of_iters_for_loop (CHREC_VARIABLE (chrec_b));

	  if (numiter_a == NULL_TREE || numiter_b == NULL_TREE)
	    {
	      if (dump_file && (dump_flags & TDF_DETAILS))
		fprintf (dump_file, "affine-affine test failed: missing iteration counts.\n");
	      *overlaps_a = chrec_dont_know;
	      *overlaps_b = chrec_dont_know;
	      *last_conflicts = chrec_dont_know;
	      goto end_analyze_subs_aa;
	    }

	  niter_a = int_cst_value (numiter_a);
	  niter_b = int_cst_value (numiter_b);
	  niter = MIN (niter_a, niter_b);

	  i0 = U[0][0] * gamma / gcd_alpha_beta;
	  j0 = U[0][1] * gamma / gcd_alpha_beta;
	  i1 = U[1][0];
	  j1 = U[1][1];

	  if ((i1 == 0 && i0 < 0)
	      || (j1 == 0 && j0 < 0))
	    {
	      /* There is no solution.  
		 FIXME: The case "i0 > nb_iterations, j0 > nb_iterations" 
		 falls in here, but for the moment we don't look at the 
		 upper bound of the iteration domain.  */
	      *overlaps_a = chrec_known;
	      *overlaps_b = chrec_known;
	      *last_conflicts = integer_zero_node;
	    }

	  else 
	    {
	      if (i1 > 0)
		{
		  tau1 = CEIL (-i0, i1);
		  tau2 = FLOOR_DIV (niter - i0, i1);

		  if (j1 > 0)
		    {
		      int last_conflict, min_multiple;
		      tau1 = MAX (tau1, CEIL (-j0, j1));
		      tau2 = MIN (tau2, FLOOR_DIV (niter - j0, j1));

		      x0 = i1 * tau1 + i0;
		      y0 = j1 * tau1 + j0;

		      /* At this point (x0, y0) is one of the
			 solutions to the Diophantine equation.  The
			 next step has to compute the smallest
			 positive solution: the first conflicts.  */
		      min_multiple = MIN (x0 / i1, y0 / j1);
		      x0 -= i1 * min_multiple;
		      y0 -= j1 * min_multiple;

		      tau1 = (x0 - i0)/i1;
		      last_conflict = tau2 - tau1;

		      /* If the overlap occurs outside of the bounds of the
			 loop, there is no dependence.  */
		      if (x0 > niter || y0  > niter)
			{
			  *overlaps_a = chrec_known;
			  *overlaps_b = chrec_known;
			  *last_conflicts = integer_zero_node;
			}
		      else
			{
			  *overlaps_a = build_polynomial_chrec
			    (1,
			     build_int_cst (NULL_TREE, x0),
			     build_int_cst (NULL_TREE, i1));
			  *overlaps_b = build_polynomial_chrec
			    (1,
			     build_int_cst (NULL_TREE, y0),
			     build_int_cst (NULL_TREE, j1));
			  *last_conflicts = build_int_cst (NULL_TREE, last_conflict);
			}
		    }
		  else
		    {
		      /* FIXME: For the moment, the upper bound of the
			 iteration domain for j is not checked.  */
		      if (dump_file && (dump_flags & TDF_DETAILS))
			fprintf (dump_file, "affine-affine test failed: unimplemented.\n");
		      *overlaps_a = chrec_dont_know;
		      *overlaps_b = chrec_dont_know;
		      *last_conflicts = chrec_dont_know;
		    }
		}
	  
	      else
		{
		  /* FIXME: For the moment, the upper bound of the
		     iteration domain for i is not checked.  */
		  if (dump_file && (dump_flags & TDF_DETAILS))
		    fprintf (dump_file, "affine-affine test failed: unimplemented.\n");
		  *overlaps_a = chrec_dont_know;
		  *overlaps_b = chrec_dont_know;
		  *last_conflicts = chrec_dont_know;
		}
	    }
	}
      else
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "affine-affine test failed: unimplemented.\n");
	  *overlaps_a = chrec_dont_know;
	  *overlaps_b = chrec_dont_know;
	  *last_conflicts = chrec_dont_know;
	}
    }

  else
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "affine-affine test failed: unimplemented.\n");
      *overlaps_a = chrec_dont_know;
      *overlaps_b = chrec_dont_know;
      *last_conflicts = chrec_dont_know;
    }

end_analyze_subs_aa:  
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "  (overlaps_a = ");
      print_generic_expr (dump_file, *overlaps_a, 0);
      fprintf (dump_file, ")\n  (overlaps_b = ");
      print_generic_expr (dump_file, *overlaps_b, 0);
      fprintf (dump_file, ")\n");
      fprintf (dump_file, ")\n");
    }
}