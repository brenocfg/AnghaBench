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
typedef  int u32 ;
typedef  int s32 ;

/* Variables and functions */

void
wlc_phy_papd_decode_epsilon(u32 epsilon, s32 *eps_real, s32 *eps_imag)
{
	*eps_imag = (epsilon >> 13);
	if (*eps_imag > 0xfff)
		*eps_imag -= 0x2000;

	*eps_real = (epsilon & 0x1fff);
	if (*eps_real > 0xfff)
		*eps_real -= 0x2000;
}