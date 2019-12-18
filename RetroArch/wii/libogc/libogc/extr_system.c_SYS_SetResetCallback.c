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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ resetcallback ;

/* Variables and functions */
 int /*<<< orphan*/  IRQMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PI_RSW ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __MaskIrq (int /*<<< orphan*/ ) ; 
 scalar_t__ __RSWCallback ; 
 int /*<<< orphan*/  __UnmaskIrq (int /*<<< orphan*/ ) ; 
 int* _piReg ; 

resetcallback SYS_SetResetCallback(resetcallback cb)
{
	u32 level;
	resetcallback old;

	_CPU_ISR_Disable(level);
	old = __RSWCallback;
	__RSWCallback = cb;
#if defined(HW_DOL)
	if(__RSWCallback) {
		_piReg[0] = 2;
		__UnmaskIrq(IRQMASK(IRQ_PI_RSW));
	} else
		__MaskIrq(IRQMASK(IRQ_PI_RSW));
#endif
	_CPU_ISR_Restore(level);
	return old;
}