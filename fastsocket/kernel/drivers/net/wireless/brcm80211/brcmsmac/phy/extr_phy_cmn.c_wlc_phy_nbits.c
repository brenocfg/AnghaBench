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
typedef  int u8 ;
typedef  int s32 ;

/* Variables and functions */
 int abs (int) ; 

u8 wlc_phy_nbits(s32 value)
{
	s32 abs_val;
	u8 nbits = 0;

	abs_val = abs(value);
	while ((abs_val >> nbits) > 0)
		nbits++;

	return nbits;
}