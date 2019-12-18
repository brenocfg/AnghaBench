#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nes_device {int int_req; int timer_int_req; int intf_int_req; int int_stat; int napi_isr_ran; int /*<<< orphan*/  dpc_tasklet; scalar_t__ regs; TYPE_1__* nesadapter; scalar_t__ msi_enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ hw_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ NE020_REV ; 
 scalar_t__ NES_INTF_INT_STAT ; 
 int NES_INT_INTF ; 
 scalar_t__ NES_INT_MASK ; 
 scalar_t__ NES_INT_PENDING ; 
 scalar_t__ NES_INT_STAT ; 
 int NES_INT_TIMER ; 
 scalar_t__ NES_TIMER_STAT ; 
 scalar_t__ nes_napi_isr (struct nes_device*) ; 
 int nes_read32 (scalar_t__) ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t nes_interrupt(int irq, void *dev_id)
{
	struct nes_device *nesdev = (struct nes_device *)dev_id;
	int handled = 0;
	u32 int_mask;
	u32 int_req;
	u32 int_stat;
	u32 intf_int_stat;
	u32 timer_stat;

	if (nesdev->msi_enabled) {
		/* No need to read the interrupt pending register if msi is enabled */
		handled = 1;
	} else {
		if (unlikely(nesdev->nesadapter->hw_rev == NE020_REV)) {
			/* Master interrupt enable provides synchronization for kicking off bottom half
			  when interrupt sharing is going on */
			int_mask = nes_read32(nesdev->regs + NES_INT_MASK);
			if (int_mask & 0x80000000) {
				/* Check interrupt status to see if this might be ours */
				int_stat = nes_read32(nesdev->regs + NES_INT_STAT);
				int_req = nesdev->int_req;
				if (int_stat&int_req) {
					/* if interesting CEQ or AEQ is pending, claim the interrupt */
					if ((int_stat&int_req) & (~(NES_INT_TIMER|NES_INT_INTF))) {
						handled = 1;
					} else {
						if (((int_stat & int_req) & NES_INT_TIMER) == NES_INT_TIMER) {
							/* Timer might be running but might be for another function */
							timer_stat = nes_read32(nesdev->regs + NES_TIMER_STAT);
							if ((timer_stat & nesdev->timer_int_req) != 0) {
								handled = 1;
							}
						}
						if ((((int_stat & int_req) & NES_INT_INTF) == NES_INT_INTF) &&
								(handled == 0)) {
							intf_int_stat = nes_read32(nesdev->regs+NES_INTF_INT_STAT);
							if ((intf_int_stat & nesdev->intf_int_req) != 0) {
								handled = 1;
							}
						}
					}
					if (handled) {
						nes_write32(nesdev->regs+NES_INT_MASK, int_mask & (~0x80000000));
						int_mask = nes_read32(nesdev->regs+NES_INT_MASK);
						/* Save off the status to save an additional read */
						nesdev->int_stat = int_stat;
						nesdev->napi_isr_ran = 1;
					}
				}
			}
		} else {
			handled = nes_read32(nesdev->regs+NES_INT_PENDING);
		}
	}

	if (handled) {

		if (nes_napi_isr(nesdev) == 0) {
			tasklet_schedule(&nesdev->dpc_tasklet);

		}
		return IRQ_HANDLED;
	} else {
		return IRQ_NONE;
	}
}