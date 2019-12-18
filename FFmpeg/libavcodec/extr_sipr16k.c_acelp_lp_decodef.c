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
 int LP_FILTER_ORDER_16k ; 
 int /*<<< orphan*/  ff_acelp_lspd2lpc (double const*,float*,int) ; 

__attribute__((used)) static void acelp_lp_decodef(float *lp_1st, float *lp_2nd,
                             const double *lsp_2nd, const double *lsp_prev)
{
    double lsp_1st[LP_FILTER_ORDER_16k];
    int i;

    /* LSP values for first subframe (3.2.5 of G.729, Equation 24) */
    for (i = 0; i < LP_FILTER_ORDER_16k; i++)
        lsp_1st[i] = (lsp_2nd[i] + lsp_prev[i]) * 0.5;

    ff_acelp_lspd2lpc(lsp_1st, lp_1st, LP_FILTER_ORDER_16k >> 1);

    /* LSP values for second subframe (3.2.5 of G.729) */
    ff_acelp_lspd2lpc(lsp_2nd, lp_2nd, LP_FILTER_ORDER_16k >> 1);
}