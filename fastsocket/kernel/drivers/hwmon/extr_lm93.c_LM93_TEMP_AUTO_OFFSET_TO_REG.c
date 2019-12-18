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

/* Variables and functions */
 int LM93_TEMP_OFFSET_TO_REG (int,int) ; 

__attribute__((used)) static u8 LM93_TEMP_AUTO_OFFSET_TO_REG(u8 old, int off, int nr, int mode)
{
	u8 new = LM93_TEMP_OFFSET_TO_REG(off, mode);

	/* temp1-temp2 (nr=0,1) use lower nibble */
	if (nr < 2)
		return (old & 0xf0) | (new & 0x0f);

	/* temp3-temp4 (nr=2,3) use upper nibble */
	else
		return (new << 4 & 0xf0) | (old & 0x0f);
}