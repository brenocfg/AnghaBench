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

/* Variables and functions */
 int IM_MEM0 ; 
 int IM_MEM1 ; 
 int IM_MEM2 ; 
 int IM_MEM3 ; 
 int /*<<< orphan*/  IM_MEMADDRESS ; 
 int /*<<< orphan*/  IRQ_MEM0 ; 
 int /*<<< orphan*/  IRQ_MEM1 ; 
 int /*<<< orphan*/  IRQ_MEM2 ; 
 int /*<<< orphan*/  IRQ_MEM3 ; 
 int /*<<< orphan*/  IRQ_MEMADDRESS ; 
 int /*<<< orphan*/  IRQ_Request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RegisterResetFunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __MEMInterruptHandler ; 
 int /*<<< orphan*/  __MaskIrq (int) ; 
 int /*<<< orphan*/  __UnmaskIrq (int /*<<< orphan*/ ) ; 
 int* _memReg ; 
 int /*<<< orphan*/  mem_resetinfo ; 

__attribute__((used)) static void __memprotect_init()
{
	u32 level;

	_CPU_ISR_Disable(level);

	__MaskIrq((IM_MEM0|IM_MEM1|IM_MEM2|IM_MEM3));

	_memReg[16] = 0;
	_memReg[8] = 255;

	IRQ_Request(IRQ_MEM0,__MEMInterruptHandler,NULL);
	IRQ_Request(IRQ_MEM1,__MEMInterruptHandler,NULL);
	IRQ_Request(IRQ_MEM2,__MEMInterruptHandler,NULL);
	IRQ_Request(IRQ_MEM3,__MEMInterruptHandler,NULL);
	IRQ_Request(IRQ_MEMADDRESS,__MEMInterruptHandler,NULL);

	SYS_RegisterResetFunc(&mem_resetinfo);
	__UnmaskIrq(IM_MEMADDRESS);		//only enable memaddress irq atm

	_CPU_ISR_Restore(level);
}