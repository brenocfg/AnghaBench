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
typedef  int /*<<< orphan*/  lambda_linear_expression ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LLE_COEFFICIENTS (int /*<<< orphan*/ ) ; 
 int LLE_CONSTANT (int /*<<< orphan*/ ) ; 
 int LLE_DENOMINATOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLE_INVARIANT_COEFFICIENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  print_linear_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char) ; 

void
print_lambda_linear_expression (FILE * outfile,
				lambda_linear_expression expr,
				int depth, int invariants, char start)
{
  fprintf (outfile, "\tLinear expression: ");
  print_linear_expression (outfile, LLE_COEFFICIENTS (expr), depth, start);
  fprintf (outfile, " constant: %d ", LLE_CONSTANT (expr));
  fprintf (outfile, "  invariants: ");
  print_linear_expression (outfile, LLE_INVARIANT_COEFFICIENTS (expr),
			   invariants, 'A');
  fprintf (outfile, "  denominator: %d\n", LLE_DENOMINATOR (expr));
}