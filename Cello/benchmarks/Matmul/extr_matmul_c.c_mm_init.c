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
 double* calloc (int,int) ; 
 scalar_t__ malloc (int) ; 

double **mm_init(int n)
{
	double **m;
	int i;
	m = (double**)malloc(n * sizeof(void*));
	for (i = 0; i < n; ++i)
		m[i] = calloc(n, sizeof(double));
	return m;
}