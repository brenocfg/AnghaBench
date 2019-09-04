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
 int /*<<< orphan*/  MAX_LP_HALF_ORDER ; 
 int /*<<< orphan*/  ff_lsp2polyf (double const*,double*,int) ; 

void ff_amrwb_lsp2lpc(const double *lsp, float *lp, int lp_order)
{
    int lp_half_order = lp_order >> 1;
    double buf[MAX_LP_HALF_ORDER + 1];
    double pa[MAX_LP_HALF_ORDER + 1];
    double *qa = buf + 1;
    int i,j;

    qa[-1] = 0.0;

    ff_lsp2polyf(lsp    , pa, lp_half_order    );
    ff_lsp2polyf(lsp + 1, qa, lp_half_order - 1);

    for (i = 1, j = lp_order - 1; i < lp_half_order; i++, j--) {
        double paf =  pa[i]            * (1 + lsp[lp_order - 1]);
        double qaf = (qa[i] - qa[i-2]) * (1 - lsp[lp_order - 1]);
        lp[i-1]  = (paf + qaf) * 0.5;
        lp[j-1]  = (paf - qaf) * 0.5;
    }

    lp[lp_half_order - 1] = (1.0 + lsp[lp_order - 1]) *
        pa[lp_half_order] * 0.5;

    lp[lp_order - 1] = lsp[lp_order - 1];
}