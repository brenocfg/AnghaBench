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
struct imxmci_host {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  pending_events; int /*<<< orphan*/  status_reg; int /*<<< orphan*/  stuck_timeout; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMXMCI_PEND_DMA_END_b ; 
 scalar_t__ MMC_REG_STATUS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void imxmci_dma_irq(int dma, void *devid)
{
	struct imxmci_host *host = devid;
	u32 stat = readw(host->base + MMC_REG_STATUS);

	atomic_set(&host->stuck_timeout, 0);
	host->status_reg = stat;
	set_bit(IMXMCI_PEND_DMA_END_b, &host->pending_events);
	tasklet_schedule(&host->tasklet);
}