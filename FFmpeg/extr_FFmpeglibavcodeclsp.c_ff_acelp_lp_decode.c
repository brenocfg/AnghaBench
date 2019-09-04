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
typedef  int int16_t ;

/* Variables and functions */
 int MAX_LP_ORDER ; 
 int /*<<< orphan*/  ff_acelp_lsp2lpc (int*,int const*,int) ; 

void ff_acelp_lp_decode(int16_t* lp_1st, int16_t* lp_2nd, const int16_t* lsp_2nd, const int16_t* lsp_prev, int lp_order)
{
    int16_t lsp_1st[MAX_LP_ORDER]; // (0.15)
    int i;

    /* LSP values for first subframe (3.2.5 of G.729, Equation 24)*/
    for(i=0; i<lp_order; i++)
#ifdef G729_BITEXACT
        lsp_1st[i] = (lsp_2nd[i] >> 1) + (lsp_prev[i] >> 1);
#else
        lsp_1st[i] = (lsp_2nd[i] + lsp_prev[i]) >> 1;
#endif

    ff_acelp_lsp2lpc(lp_1st, lsp_1st, lp_order >> 1);

    /* LSP values for second subframe (3.2.5 of G.729)*/
    ff_acelp_lsp2lpc(lp_2nd, lsp_2nd, lp_order >> 1);
}