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
typedef  int /*<<< orphan*/  lambda_loop ;
typedef  int /*<<< orphan*/ * lambda_linear_expression ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * LLE_NEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LL_LINEAR_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LL_LOWER_BOUND (int /*<<< orphan*/ ) ; 
 int LL_STEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LL_UPPER_BOUND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_lambda_linear_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,char) ; 

void
print_lambda_loop (FILE * outfile, lambda_loop loop, int depth,
		   int invariants, char start)
{
  int step;
  lambda_linear_expression expr;

  gcc_assert (loop);

  expr = LL_LINEAR_OFFSET (loop);
  step = LL_STEP (loop);
  fprintf (outfile, "  step size = %d \n", step);

  if (expr)
    {
      fprintf (outfile, "  linear offset: \n");
      print_lambda_linear_expression (outfile, expr, depth, invariants,
				      start);
    }

  fprintf (outfile, "  lower bound: \n");
  for (expr = LL_LOWER_BOUND (loop); expr != NULL; expr = LLE_NEXT (expr))
    print_lambda_linear_expression (outfile, expr, depth, invariants, start);
  fprintf (outfile, "  upper bound: \n");
  for (expr = LL_UPPER_BOUND (loop); expr != NULL; expr = LLE_NEXT (expr))
    print_lambda_linear_expression (outfile, expr, depth, invariants, start);
}