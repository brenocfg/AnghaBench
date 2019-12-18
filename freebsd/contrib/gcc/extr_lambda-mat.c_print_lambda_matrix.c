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
typedef  int /*<<< orphan*/ * lambda_matrix ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_lambda_vector (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
print_lambda_matrix (FILE * outfile, lambda_matrix matrix, int m, int n)
{
  int i;

  for (i = 0; i < m; i++)
    print_lambda_vector (outfile, matrix[i], n);
  fprintf (outfile, "\n");
}