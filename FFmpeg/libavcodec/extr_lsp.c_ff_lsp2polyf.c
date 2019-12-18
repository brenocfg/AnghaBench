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

void ff_lsp2polyf(const double *lsp, double *f, int lp_half_order)
{
    int i, j;

    f[0] = 1.0;
    f[1] = -2 * lsp[0];
    lsp -= 2;
    for(i=2; i<=lp_half_order; i++)
    {
        double val = -2 * lsp[2*i];
        f[i] = val * f[i-1] + 2*f[i-2];
        for(j=i-1; j>1; j--)
            f[j] += f[j-1] * val + f[j-2];
        f[1] += val;
    }
}