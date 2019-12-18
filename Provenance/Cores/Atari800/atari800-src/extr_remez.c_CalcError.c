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
 double ComputeA (double const,int,double const*,double const*,double const*) ; 

__attribute__((used)) static void CalcError(int r, const double ad[],
                      const double x[], const double y[],
                      int gridsize, const double Grid[],
                      const double D[], const double W[], double E[])
{
	int i;
	double A;

	for (i = 0; i < gridsize; i++) {
		A = ComputeA(Grid[i], r, ad, x, y);
		E[i] = W[i] * (D[i] - A);
	}
}