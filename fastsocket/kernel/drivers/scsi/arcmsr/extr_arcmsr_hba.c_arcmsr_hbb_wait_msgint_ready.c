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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct MessageUnit_B {int /*<<< orphan*/  drv2iop_doorbell; int /*<<< orphan*/  iop2drv_doorbell; } ;
struct AdapterControlBlock {struct MessageUnit_B* pmuB; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_DRV2IOP_END_OF_INTERRUPT ; 
 int ARCMSR_IOP2DRV_MESSAGE_CMD_DONE ; 
 int /*<<< orphan*/  ARCMSR_MESSAGE_INT_CLEAR_PATTERN ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t arcmsr_hbb_wait_msgint_ready(struct AdapterControlBlock *acb)
{
	struct MessageUnit_B *reg = acb->pmuB;
	uint32_t Index;
	uint8_t Retries = 0x00;
	do {
		for (Index = 0; Index < 100; Index++) {
			if (readl(reg->iop2drv_doorbell)
				& ARCMSR_IOP2DRV_MESSAGE_CMD_DONE) {
				writel(ARCMSR_MESSAGE_INT_CLEAR_PATTERN
					, reg->iop2drv_doorbell);
				writel(ARCMSR_DRV2IOP_END_OF_INTERRUPT, reg->drv2iop_doorbell);
				return true;
			}
			msleep(10);
		}/*max 1 seconds*/

	} while (Retries++ < 20);/*max 20 sec*/
	return false;
}