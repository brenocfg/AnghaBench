#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int scale; } ;
struct TYPE_5__ {TYPE_1__ regular; void* y; void* x; } ;
typedef  TYPE_2__ ccv_keypoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_max (double,int) ; 
 void* ccv_min (int /*<<< orphan*/ ,int) ; 
 double fabs (double) ; 

__attribute__((used)) inline static double _ccv_keypoint_interpolate(float N9[3][9], int ix, int iy, int is, ccv_keypoint_t* kp)
{
	double Dxx = N9[1][3] - 2 * N9[1][4] + N9[1][5]; 
	double Dyy = N9[1][1] - 2 * N9[1][4] + N9[1][7];
	double Dxy = (N9[1][8] - N9[1][6] - N9[1][2] + N9[1][0]) * 0.25;
	double score = (Dxx + Dyy) * (Dxx + Dyy) / (Dxx * Dyy - Dxy * Dxy);
	double Dx = (N9[1][5] - N9[1][3]) * 0.5;
	double Dy = (N9[1][7] - N9[1][1]) * 0.5;
	double Ds = (N9[2][4] - N9[0][4]) * 0.5;
	double Dxs = (N9[2][5] + N9[0][3] - N9[2][3] - N9[0][5]) * 0.25;
	double Dys = (N9[2][7] + N9[0][1] - N9[2][1] - N9[0][7]) * 0.25;
	double Dss = N9[0][4] - 2 * N9[1][4] + N9[2][4];
	double A[3][3] = { { Dxx, Dxy, Dxs },
					   { Dxy, Dyy, Dys },
					   { Dxs, Dys, Dss } };
	double b[3] = { -Dx, -Dy, -Ds };
	/* Gauss elimination */
	int i, j, ii, jj;
	for(j = 0; j < 3; j++)
	{
		double maxa = 0;
		double maxabsa = 0;
		int maxi = j;
		double tmp;

		/* look for the maximally stable pivot */
		for (i = j; i < 3; i++)
		{
			double a = A[i][j];
			double absa = fabs(a);
			if (absa > maxabsa)
			{
				maxa = a;
				maxabsa = absa;
				maxi = i;
			}
		}

		/* if singular give up */
		if (maxabsa < 1e-10f)
		{
			b[0] = b[1] = b[2] = 0;
			break;
		}

		i = maxi;

		/* swap j-th row with i-th row and normalize j-th row */
		for(jj = j; jj < 3; jj++)
		{
			tmp = A[i][jj];
			A[i][jj] = A[j][jj];
			A[j][jj] = tmp;
			A[j][jj] /= maxa;
		}
		tmp = b[j];
		b[j] = b[i];
		b[i] = tmp;
		b[j] /= maxa;

		/* elimination */
		for (ii = j + 1; ii < 3; ii++)
		{
			double x = A[ii][j];
			for (jj = j; jj < 3; jj++)
				A[ii][jj] -= x * A[j][jj];
			b[ii] -= x * b[j];
		}
	}

	/* backward substitution */
	for (i = 2; i > 0; i--)
	{
		double x = b[i];
		for (ii = i - 1; ii >= 0; ii--)
		  b[ii] -= x * A[ii][i];
	}
	kp->x = ix + ccv_min(ccv_max(b[0], -1), 1);
	kp->y = iy + ccv_min(ccv_max(b[1], -1), 1);
	kp->regular.scale = is + b[2];
	return score;
}