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
 int /*<<< orphan*/  IRQMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_DSP_ARAM ; 
 int /*<<< orphan*/  IRQ_Request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int* __ARBlockLen ; 
 int /*<<< orphan*/  __ARCheckSize () ; 
 int /*<<< orphan*/ * __ARDmaCallback ; 
 int __ARFreeBlocks ; 
 int /*<<< orphan*/  __ARHandler ; 
 int __ARInit_Flag ; 
 int __ARStackPointer ; 
 int /*<<< orphan*/  __UnmaskIrq (int /*<<< orphan*/ ) ; 
 int* _dspReg ; 

u32 AR_Init(u32 *stack_idx_array,u32 num_entries)
{
	u32 level;
	u32 aram_base = 0x4000;

	if(__ARInit_Flag) return aram_base;

	_CPU_ISR_Disable(level);

	__ARDmaCallback = NULL;

	IRQ_Request(IRQ_DSP_ARAM,__ARHandler,NULL);
	__UnmaskIrq(IRQMASK(IRQ_DSP_ARAM));

	__ARStackPointer = aram_base;
	__ARFreeBlocks = num_entries;
	__ARBlockLen = stack_idx_array;
	_dspReg[13] = (_dspReg[13]&~0xff)|(_dspReg[13]&0xff);

	__ARCheckSize();
	__ARInit_Flag = 1;

	_CPU_ISR_Restore(level);
	return __ARStackPointer;
}