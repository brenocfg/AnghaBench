#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct memstick_host {int dummy; } ;
struct jmb38x_ms_host {int cmd_flags; int io_pos; int /*<<< orphan*/  lock; TYPE_3__* req; scalar_t__ addr; TYPE_2__* chip; void** io_word; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {scalar_t__ data_dir; int /*<<< orphan*/  error; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CMD_READY ; 
 int DMA_DATA ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ETIME ; 
 int FIFO_READY ; 
 scalar_t__ INT_STATUS ; 
 unsigned int INT_STATUS_ANY_ERR ; 
 unsigned int INT_STATUS_CRC_ERR ; 
 unsigned int INT_STATUS_EOTPC ; 
 unsigned int INT_STATUS_EOTRAN ; 
 unsigned int INT_STATUS_FIFO_RRDY ; 
 unsigned int INT_STATUS_FIFO_WRDY ; 
 unsigned int INT_STATUS_MEDIA_IN ; 
 unsigned int INT_STATUS_MEDIA_OUT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ READ ; 
 int REG_DATA ; 
 scalar_t__ TPC_P0 ; 
 scalar_t__ TPC_P1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  jmb38x_ms_complete_cmd (struct memstick_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmb38x_ms_transfer_data (struct jmb38x_ms_host*) ; 
 int /*<<< orphan*/  memstick_detect_change (struct memstick_host*) ; 
 struct jmb38x_ms_host* memstick_priv (struct memstick_host*) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t jmb38x_ms_isr(int irq, void *dev_id)
{
	struct memstick_host *msh = dev_id;
	struct jmb38x_ms_host *host = memstick_priv(msh);
	unsigned int irq_status;

	spin_lock(&host->lock);
	irq_status = readl(host->addr + INT_STATUS);
	dev_dbg(&host->chip->pdev->dev, "irq_status = %08x\n", irq_status);
	if (irq_status == 0 || irq_status == (~0)) {
		spin_unlock(&host->lock);
		return IRQ_NONE;
	}

	if (host->req) {
		if (irq_status & INT_STATUS_ANY_ERR) {
			if (irq_status & INT_STATUS_CRC_ERR)
				host->req->error = -EILSEQ;
			else
				host->req->error = -ETIME;
		} else {
			if (host->cmd_flags & DMA_DATA) {
				if (irq_status & INT_STATUS_EOTRAN)
					host->cmd_flags |= FIFO_READY;
			} else {
				if (irq_status & (INT_STATUS_FIFO_RRDY
						  | INT_STATUS_FIFO_WRDY))
					jmb38x_ms_transfer_data(host);

				if (irq_status & INT_STATUS_EOTRAN) {
					jmb38x_ms_transfer_data(host);
					host->cmd_flags |= FIFO_READY;
				}
			}

			if (irq_status & INT_STATUS_EOTPC) {
				host->cmd_flags |= CMD_READY;
				if (host->cmd_flags & REG_DATA) {
					if (host->req->data_dir == READ) {
						host->io_word[0]
							= readl(host->addr
								+ TPC_P0);
						host->io_word[1]
							= readl(host->addr
								+ TPC_P1);
						host->io_pos = 8;

						jmb38x_ms_transfer_data(host);
					}
					host->cmd_flags |= FIFO_READY;
				}
			}
		}
	}

	if (irq_status & (INT_STATUS_MEDIA_IN | INT_STATUS_MEDIA_OUT)) {
		dev_dbg(&host->chip->pdev->dev, "media changed\n");
		memstick_detect_change(msh);
	}

	writel(irq_status, host->addr + INT_STATUS);

	if (host->req
	    && (((host->cmd_flags & CMD_READY)
		 && (host->cmd_flags & FIFO_READY))
		|| host->req->error))
		jmb38x_ms_complete_cmd(msh, 0);

	spin_unlock(&host->lock);
	return IRQ_HANDLED;
}