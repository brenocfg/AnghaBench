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
struct imxmci_host {int imask; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  pending_events; int /*<<< orphan*/  status_reg; int /*<<< orphan*/  stuck_timeout; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMXMCI_PEND_IRQ_b ; 
 int /*<<< orphan*/  IMXMCI_PEND_STARTED_b ; 
 int INT_MASK_AUTO_CARD_DETECT ; 
 int INT_MASK_SDIO ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 scalar_t__ MMC_REG_INT_MASK ; 
 scalar_t__ MMC_REG_STATUS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t imxmci_irq(int irq, void *devid)
{
	struct imxmci_host *host = devid;
	u32 stat = readw(host->base + MMC_REG_STATUS);
	int handled = 1;

	writew(host->imask | INT_MASK_SDIO | INT_MASK_AUTO_CARD_DETECT,
			host->base + MMC_REG_INT_MASK);

	atomic_set(&host->stuck_timeout, 0);
	host->status_reg = stat;
	set_bit(IMXMCI_PEND_IRQ_b, &host->pending_events);
	set_bit(IMXMCI_PEND_STARTED_b, &host->pending_events);
	tasklet_schedule(&host->tasklet);

	return IRQ_RETVAL(handled);
}