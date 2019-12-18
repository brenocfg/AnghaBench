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
 int GRIDDENSITY ; 
 int NEGATIVE ; 

__attribute__((used)) static void CreateDenseGrid(int r, int numtaps, int numband, double bands[],
                            const double des[], const double weight[],
                            int *gridsize, double Grid[],
                            double D[], double W[], int symmetry)
{
	int i, j, k, band;
	double delf, lowf, highf;

	delf = 0.5 / (GRIDDENSITY * r);

	/* For differentiator, hilbert,
	 *   symmetry is odd and Grid[0] = max(delf, band[0]) */

	if (symmetry == NEGATIVE && delf > bands[0])
		bands[0] = delf;

	j = 0;
	for (band = 0; band < numband; band++) {
		Grid[j] = bands[2 * band];
		lowf = bands[2 * band];
		highf = bands[2 * band + 1];
		k = (int) ((highf - lowf) / delf + 0.5); /* .5 for rounding */
		for (i = 0; i < k; i++) {
			D[j] = des[band];
			W[j] = weight[band];
			Grid[j] = lowf;
			lowf += delf;
			j++;
		}
		Grid[j - 1] = highf;
	}

	/* Similar to above, if odd symmetry, last grid point can't be .5
	 *  - but, if there are even taps, leave the last grid point at .5 */
	if ((symmetry == NEGATIVE) &&
	   (Grid[*gridsize - 1] > (0.5 - delf)) &&
	   (numtaps % 2))
	{
		Grid[*gridsize - 1] = 0.5 - delf;
	}
}