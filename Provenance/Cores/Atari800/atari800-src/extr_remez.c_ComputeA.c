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
 double Pi2 ; 
 double cos (double) ; 
 double fabs (double) ; 

__attribute__((used)) static double ComputeA(double freq, int r, const double ad[],
                       const double x[], const double y[])
{
	int i;
	double xc, c, denom, numer;

	denom = numer = 0;
	xc = cos(Pi2 * freq);
	for (i = 0; i <= r; i++) {
		c = xc - x[i];
		if (fabs(c) < 1.0e-7) {
			numer = y[i];
			denom = 1;
			break;
		}
		c = ad[i] / c;
		denom += c;
		numer += c * y[i];
	}
	return numer / denom;
}