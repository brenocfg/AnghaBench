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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int IM_MEM0 ; 
 int IM_MEM1 ; 
 int IM_MEM2 ; 
 int IM_MEM3 ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  __UnmaskIrq (int) ; 
 int* _memReg ; 

__attribute__((used)) static s32 __mem_onreset(s32 final)
{
	if(final==TRUE) {
		_memReg[8] = 255;
		__UnmaskIrq(IM_MEM0|IM_MEM1|IM_MEM2|IM_MEM3);
	}
	return 1;
}