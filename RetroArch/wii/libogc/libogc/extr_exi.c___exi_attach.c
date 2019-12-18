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
struct TYPE_3__ {int flags; int /*<<< orphan*/  CallbackEXT; } ;
typedef  TYPE_1__ exibus_priv ;
typedef  int /*<<< orphan*/  EXICallback ;

/* Variables and functions */
 int EXI_FLAG_ATTACH ; 
 size_t IRQMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_EXI0_EXT ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __UnmaskIrq (size_t) ; 
 int /*<<< orphan*/  __exi_clearirqs (size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __exi_probe (size_t) ; 
 TYPE_1__* eximap ; 

__attribute__((used)) static s32 __exi_attach(s32 nChn,EXICallback ext_cb)
{
	s32 ret;
	u32 level;
	exibus_priv *exi = &eximap[nChn];
	_CPU_ISR_Disable(level);
	ret = 0;
	if(!(exi->flags&EXI_FLAG_ATTACH)) {
		if(__exi_probe(nChn)==1) {
			__exi_clearirqs(nChn,1,0,0);
			exi->CallbackEXT = ext_cb;
			__UnmaskIrq(((IRQMASK(IRQ_EXI0_EXT))>>(nChn*3)));
			exi->flags |= EXI_FLAG_ATTACH;
			ret = 1;
		}
	}
	_CPU_ISR_Restore(level);
	return ret;
}