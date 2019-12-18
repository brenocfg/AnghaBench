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
 int /*<<< orphan*/  mm_destroy (int,double**) ; 
 double** mm_gen (int) ; 
 double** mm_mul (int,double**,double**) ; 

int main(int argc, char *argv[])
{
	int n = 300;
	double **a, **b, **m;
	n = (n/2) * 2;
	a = mm_gen(n); b = mm_gen(n);
	m = mm_mul(n, a, b);
	//fprintf(stderr, "%lf\n", m[n/2][n/2]);
	mm_destroy(n, a); mm_destroy(n, b); mm_destroy(n, m);
	return 0;
}