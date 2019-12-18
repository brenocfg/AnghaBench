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
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 size_t fls (size_t) ; 

void wlc_phy_compute_dB(u32 *cmplx_pwr, s8 *p_cmplx_pwr_dB, u8 core)
{
	u8 msb, secondmsb, i;
	u32 tmp;

	for (i = 0; i < core; i++) {
		secondmsb = 0;
		tmp = cmplx_pwr[i];
		msb = fls(tmp);
		if (msb)
			secondmsb = (u8) ((tmp >> (--msb - 1)) & 1);
		p_cmplx_pwr_dB[i] = (s8) (3 * msb + 2 * secondmsb);
	}
}