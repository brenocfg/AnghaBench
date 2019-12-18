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
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 int PS_MAX_NR_IPDOPD ; 

__attribute__((used)) static void ipdopd_reset(int8_t *ipd_hist, int8_t *opd_hist)
{
    int i;
    for (i = 0; i < PS_MAX_NR_IPDOPD; i++) {
        opd_hist[i] = 0;
        ipd_hist[i] = 0;
    }
}