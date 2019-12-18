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

/* Variables and functions */
 int /*<<< orphan*/  LCAllocTags (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int /*<<< orphan*/  __LCEnable () ; 
 int mfspr (int) ; 

void LCAlloc(void *addr,u32 bytes)
{
	u32 level;
	u32 cnt = bytes>>5;
	u32 hid2 = mfspr(920);
	if(!(hid2&0x10000000)) {
		_CPU_ISR_Disable(level);
		__LCEnable();
		_CPU_ISR_Restore(level);
	}
	LCAllocTags(TRUE,addr,cnt);
}