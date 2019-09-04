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
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ FLT_EPSILON ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,double,int) ; 
 scalar_t__ fabs (double) ; 
 int /*<<< orphan*/  multiply (double,double,int,double*) ; 

__attribute__((used)) static int expand(AVFilterContext *ctx, double *pz, int nb, double *coeffs)
{
    int i;

    coeffs[0] = 1.0;
    coeffs[1] = 0.0;

    for (i = 0; i < nb; i++) {
        coeffs[2 * (i + 1)    ] = 0.0;
        coeffs[2 * (i + 1) + 1] = 0.0;
    }

    for (i = 0; i < nb; i++)
        multiply(pz[2 * i], pz[2 * i + 1], nb, coeffs);

    for (i = 0; i < nb + 1; i++) {
        if (fabs(coeffs[2 * i + 1]) > FLT_EPSILON) {
            av_log(ctx, AV_LOG_ERROR, "coeff: %f of z^%d is not real; poles/zeros are not complex conjugates.\n",
                   coeffs[2 * i + 1], i);
            return AVERROR(EINVAL);
        }
    }

    return 0;
}