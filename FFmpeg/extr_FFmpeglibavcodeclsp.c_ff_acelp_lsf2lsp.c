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
 int ff_cos (int const) ; 

void ff_acelp_lsf2lsp(int16_t *lsp, const int16_t *lsf, int lp_order)
{
    int i;

    /* Convert LSF to LSP, lsp=cos(lsf) */
    for(i=0; i<lp_order; i++)
        // 20861 = 2.0 / PI in (0.15)
        lsp[i] = ff_cos(lsf[i] * 20861 >> 15); // divide by PI and (0,13) -> (0,14)
}