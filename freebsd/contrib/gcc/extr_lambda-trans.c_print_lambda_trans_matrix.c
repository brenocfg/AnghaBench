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
typedef  int /*<<< orphan*/  lambda_trans_matrix ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LTM_COLSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LTM_MATRIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LTM_ROWSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_lambda_matrix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
print_lambda_trans_matrix (FILE *outfile, lambda_trans_matrix mat)
{
  print_lambda_matrix (outfile, LTM_MATRIX (mat), LTM_ROWSIZE (mat), 
		       LTM_COLSIZE (mat));
}