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

/* Variables and functions */
 double** mm_init (int) ; 

double **mm_gen(int n)
{
	double **m, tmp = 1. / n / n;
	int i, j;
	m = mm_init(n);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			m[i][j] = tmp * (i - j) * (i + j);
	return m;
}