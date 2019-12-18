#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct memstick_host {int /*<<< orphan*/  dev; } ;
struct jmb38x_ms_host {int cmd_flags; TYPE_2__* req; scalar_t__ addr; TYPE_1__* chip; int /*<<< orphan*/  timer; } ;
struct TYPE_4__ {int int_reg; scalar_t__ data_dir; int /*<<< orphan*/  error; int /*<<< orphan*/  sg; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ BLOCK ; 
 scalar_t__ DMA_CONTROL ; 
 int DMA_DATA ; 
 int /*<<< orphan*/  ETIME ; 
 scalar_t__ HOST_CONTROL ; 
 unsigned int HOST_CONTROL_LED ; 
 scalar_t__ INT_SIGNAL_ENABLE ; 
 scalar_t__ INT_STATUS ; 
 scalar_t__ INT_STATUS_ENABLE ; 
 unsigned int INT_STATUS_FIFO_RRDY ; 
 unsigned int INT_STATUS_FIFO_WRDY ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ READ ; 
 scalar_t__ STATUS ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int) ; 
 scalar_t__ jmb38x_ms_issue_cmd (struct memstick_host*) ; 
 int memstick_next_req (struct memstick_host*,TYPE_2__**) ; 
 struct jmb38x_ms_host* memstick_priv (struct memstick_host*) ; 
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void jmb38x_ms_complete_cmd(struct memstick_host *msh, int last)
{
	struct jmb38x_ms_host *host = memstick_priv(msh);
	unsigned int t_val = 0;
	int rc;

	del_timer(&host->timer);

	dev_dbg(&msh->dev, "c control %08x\n",
		readl(host->addr + HOST_CONTROL));
	dev_dbg(&msh->dev, "c status %08x\n",
		readl(host->addr + INT_STATUS));
	dev_dbg(&msh->dev, "c hstatus %08x\n", readl(host->addr + STATUS));

	host->req->int_reg = readl(host->addr + STATUS) & 0xff;

	writel(0, host->addr + BLOCK);
	writel(0, host->addr + DMA_CONTROL);

	if (host->cmd_flags & DMA_DATA) {
		pci_unmap_sg(host->chip->pdev, &host->req->sg, 1,
			     host->req->data_dir == READ
			     ? PCI_DMA_FROMDEVICE : PCI_DMA_TODEVICE);
	} else {
		t_val = readl(host->addr + INT_STATUS_ENABLE);
		if (host->req->data_dir == READ)
			t_val &= ~INT_STATUS_FIFO_RRDY;
		else
			t_val &= ~INT_STATUS_FIFO_WRDY;

		writel(t_val, host->addr + INT_STATUS_ENABLE);
		writel(t_val, host->addr + INT_SIGNAL_ENABLE);
	}

	writel((~HOST_CONTROL_LED) & readl(host->addr + HOST_CONTROL),
	       host->addr + HOST_CONTROL);

	if (!last) {
		do {
			rc = memstick_next_req(msh, &host->req);
		} while (!rc && jmb38x_ms_issue_cmd(msh));
	} else {
		do {
			rc = memstick_next_req(msh, &host->req);
			if (!rc)
				host->req->error = -ETIME;
		} while (!rc);
	}
}