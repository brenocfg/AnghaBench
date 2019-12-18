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
 int /*<<< orphan*/  MAX_LP_HALF_ORDER ; 
 int /*<<< orphan*/  lsp2poly (int*,int const*,int) ; 

void ff_acelp_lsp2lpc(int16_t* lp, const int16_t* lsp, int lp_half_order)
{
    int i;
    int f1[MAX_LP_HALF_ORDER+1]; // (3.22)
    int f2[MAX_LP_HALF_ORDER+1]; // (3.22)

    lsp2poly(f1, lsp  , lp_half_order);
    lsp2poly(f2, lsp+1, lp_half_order);

    /* 3.2.6 of G.729, Equations 25 and  26*/
    lp[0] = 4096;
    for(i=1; i<lp_half_order+1; i++)
    {
        int ff1 = f1[i] + f1[i-1]; // (3.22)
        int ff2 = f2[i] - f2[i-1]; // (3.22)

        ff1 += 1 << 10; // for rounding
        lp[i]    = (ff1 + ff2) >> 11; // divide by 2 and (3.22) -> (3.12)
        lp[(lp_half_order << 1) + 1 - i] = (ff1 - ff2) >> 11; // divide by 2 and (3.22) -> (3.12)
    }
}