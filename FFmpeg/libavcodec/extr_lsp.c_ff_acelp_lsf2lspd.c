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
 double M_PI ; 
 double cos (double) ; 

void ff_acelp_lsf2lspd(double *lsp, const float *lsf, int lp_order)
{
    int i;

    for(i = 0; i < lp_order; i++)
        lsp[i] = cos(2.0 * M_PI * lsf[i]);
}