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
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int __SetInterrupts (int,int) ; 
 int currIrqMask ; 
 int prevIrqMask ; 

void __UnmaskIrq(u32 nMask)
{
	u32 level;
	u32 mask;

	_CPU_ISR_Disable(level);
	mask = (nMask&(prevIrqMask|currIrqMask));
	nMask = (prevIrqMask&~nMask);
	prevIrqMask = nMask;
	while((mask=__SetInterrupts(mask,(nMask|currIrqMask)))!=0);
	_CPU_ISR_Restore(level);
}