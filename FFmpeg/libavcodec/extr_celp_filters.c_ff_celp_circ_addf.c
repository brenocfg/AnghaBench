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

void ff_celp_circ_addf(float *out, const float *in,
                       const float *lagged, int lag, float fac, int n)
{
    int k;
    for (k = 0; k < lag; k++)
        out[k] = in[k] + fac * lagged[n + k - lag];
    for (; k < n; k++)
        out[k] = in[k] + fac * lagged[    k - lag];
}