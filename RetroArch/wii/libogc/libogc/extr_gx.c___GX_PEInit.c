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

/* Variables and functions */
 int /*<<< orphan*/  IRQMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PI_PEFINISH ; 
 int /*<<< orphan*/  IRQ_PI_PETOKEN ; 
 int /*<<< orphan*/  IRQ_Request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __GXFinishInterruptHandler ; 
 int /*<<< orphan*/  __GXTokenInterruptHandler ; 
 int /*<<< orphan*/  __UnmaskIrq (int /*<<< orphan*/ ) ; 
 int* _peReg ; 

__attribute__((used)) static void __GX_PEInit()
{
	IRQ_Request(IRQ_PI_PETOKEN,__GXTokenInterruptHandler,NULL);
	__UnmaskIrq(IRQMASK(IRQ_PI_PETOKEN));

	IRQ_Request(IRQ_PI_PEFINISH,__GXFinishInterruptHandler,NULL);
	__UnmaskIrq(IRQMASK(IRQ_PI_PEFINISH));

	_peReg[5] = 0x0F;
}