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
typedef  int /*<<< orphan*/ ** lambda_matrix ;

/* Variables and functions */

void
lambda_matrix_delete_rows (lambda_matrix mat, int rows, int from, int to)
{
  int i;
  int dist;
  dist = to - from;

  for (i = to; i < rows; i++)
    mat[i - dist] = mat[i];

  for (i = rows - dist; i < rows; i++)
    mat[i] = NULL;
}