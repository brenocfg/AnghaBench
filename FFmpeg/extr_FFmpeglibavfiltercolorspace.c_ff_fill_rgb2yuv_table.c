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
struct LumaCoefficients {double cr; double cg; double cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  gbr_matrix ; 
 int /*<<< orphan*/  memcpy (double**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ycgco_matrix ; 

void ff_fill_rgb2yuv_table(const struct LumaCoefficients *coeffs,
                           double rgb2yuv[3][3])
{
    double bscale, rscale;

    // special ycgco matrix
    if (coeffs->cr == 0.25 && coeffs->cg == 0.5 && coeffs->cb == 0.25) {
        memcpy(rgb2yuv, ycgco_matrix, sizeof(double) * 9);
        return;
    } else if (coeffs->cr == 1 && coeffs->cg == 1 && coeffs->cb == 1) {
        memcpy(rgb2yuv, gbr_matrix, sizeof(double) * 9);
        return;
    }

    rgb2yuv[0][0] = coeffs->cr;
    rgb2yuv[0][1] = coeffs->cg;
    rgb2yuv[0][2] = coeffs->cb;
    bscale = 0.5 / (coeffs->cb - 1.0);
    rscale = 0.5 / (coeffs->cr - 1.0);
    rgb2yuv[1][0] = bscale * coeffs->cr;
    rgb2yuv[1][1] = bscale * coeffs->cg;
    rgb2yuv[1][2] = 0.5;
    rgb2yuv[2][0] = 0.5;
    rgb2yuv[2][1] = rscale * coeffs->cg;
    rgb2yuv[2][2] = rscale * coeffs->cb;
}