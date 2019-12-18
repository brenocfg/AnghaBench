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
struct irq_handler_s {int dummy; } ;

/* Variables and functions */
 int CPU_MINIMUM_STACK_FRAME_SIZE ; 
 int CPU_STACK_ALIGNMENT ; 
 int /*<<< orphan*/  IM_PI_ERROR ; 
 int /*<<< orphan*/  __MaskIrq (int) ; 
 int /*<<< orphan*/  __UnmaskIrq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __intrstack_addr ; 
 int /*<<< orphan*/  __intrstack_end ; 
 int* _piReg ; 
 scalar_t__ currIrqMask ; 
 int /*<<< orphan*/  g_IRQHandler ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtspr (int,int) ; 
 scalar_t__ prevIrqMask ; 

void __irq_init()
{
	register u32 intrStack = (u32)__intrstack_addr;
	register u32 intrStack_end = (u32)__intrstack_end;
	register u32 irqNestingLevel = 0;

	memset(g_IRQHandler,0,32*sizeof(struct irq_handler_s));

	*((u32*)intrStack_end) = 0xDEADBEEF;
	intrStack = intrStack - CPU_MINIMUM_STACK_FRAME_SIZE;
	intrStack &= ~(CPU_STACK_ALIGNMENT-1);
	*((u32*)intrStack) = 0;

	mtspr(272,irqNestingLevel);
	mtspr(273,intrStack);

	prevIrqMask = 0;
	currIrqMask = 0;
	_piReg[1] = 0xf0;

	__MaskIrq(-32);

	_piReg[0] = 0x01;
	__UnmaskIrq(IM_PI_ERROR);
}