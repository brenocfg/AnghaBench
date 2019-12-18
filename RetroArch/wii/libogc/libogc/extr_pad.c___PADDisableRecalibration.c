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
typedef  int u32 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 

u32 __PADDisableRecalibration(s32 disable)
{
	u32 level,ret;
	u8 *ram_recaldis = (u8*)0x800030e3;

	_CPU_ISR_Disable(level);

	ret = 0;
	if(ram_recaldis[0]&0x40) ret = 1;

	ram_recaldis[0] &= 0xbf;
	if(disable) ram_recaldis[0] |= 0x40;

	_CPU_ISR_Restore(level);

	return ret;
}