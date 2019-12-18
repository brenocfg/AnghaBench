#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t s32 ;
struct TYPE_3__ {int flags; scalar_t__ lockeddev; } ;
typedef  TYPE_1__ exibus_priv ;

/* Variables and functions */
 scalar_t__ EXI_DEVICE_0 ; 
 int EXI_FLAG_ATTACH ; 
 int EXI_FLAG_LOCKED ; 
 size_t IRQMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_EXI0_EXI ; 
 int /*<<< orphan*/  IRQ_EXI0_EXT ; 
 int /*<<< orphan*/  IRQ_EXI0_TC ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __MaskIrq (size_t) ; 
 TYPE_1__* eximap ; 

s32 EXI_Detach(s32 nChn)
{
	u32 level;
	s32 ret = 1;
	exibus_priv *exi = &eximap[nChn];
	_CPU_ISR_Disable(level);
	if(exi->flags&EXI_FLAG_ATTACH) {
		if(exi->flags&EXI_FLAG_LOCKED && exi->lockeddev!=EXI_DEVICE_0) ret = 0;
		else {
			exi->flags &= ~EXI_FLAG_ATTACH;
			__MaskIrq(((IRQMASK(IRQ_EXI0_EXI)|IRQMASK(IRQ_EXI0_TC)|IRQMASK(IRQ_EXI0_EXT))>>(nChn*3)));
		}
	}
	_CPU_ISR_Restore(level);
	return ret;
}