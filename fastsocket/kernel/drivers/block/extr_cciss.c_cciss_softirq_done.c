#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_26__ {int /*<<< orphan*/  val; TYPE_4__ val32; } ;
typedef  TYPE_7__ u64bit ;
struct request {scalar_t__ cmd_type; scalar_t__ errors; int /*<<< orphan*/  resid_len; TYPE_10__* completion_data; } ;
struct TYPE_27__ {int /*<<< orphan*/  lock; TYPE_11__* pdev; TYPE_9__** cmd_sg_list; } ;
typedef  TYPE_8__ ctlr_info_t ;
struct TYPE_24__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_28__ {scalar_t__ Ext; int /*<<< orphan*/  Len; TYPE_5__ Addr; } ;
struct TYPE_25__ {int /*<<< orphan*/  ResidualCnt; } ;
struct TYPE_22__ {int SGList; } ;
struct TYPE_20__ {scalar_t__ Direction; } ;
struct TYPE_21__ {TYPE_1__ Type; } ;
struct TYPE_19__ {int /*<<< orphan*/  dev; } ;
struct TYPE_18__ {size_t ctlr; size_t cmdindex; TYPE_6__* err_info; TYPE_3__ Header; TYPE_2__ Request; TYPE_9__* SG; } ;
typedef  TYPE_9__ SGDescriptor_struct ;
typedef  TYPE_10__ CommandList_struct ;

/* Variables and functions */
 scalar_t__ CCISS_SG_CHAIN ; 
 int /*<<< orphan*/  EIO ; 
 int PCI_DMA_FROMDEVICE ; 
 int PCI_DMA_TODEVICE ; 
 scalar_t__ REQ_TYPE_BLOCK_PC ; 
 scalar_t__ XFER_READ ; 
 int /*<<< orphan*/  blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cciss_check_queues (TYPE_8__*) ; 
 int /*<<< orphan*/  cciss_unmap_sg_chain_block (TYPE_8__*,TYPE_10__*) ; 
 int /*<<< orphan*/  cmd_free (TYPE_8__*,TYPE_10__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct request*) ; 
 TYPE_8__** hba ; 
 int /*<<< orphan*/  pci_unmap_page (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cciss_softirq_done(struct request *rq)
{
	CommandList_struct *c = rq->completion_data;
	ctlr_info_t *h = hba[c->ctlr];
	SGDescriptor_struct *curr_sg = c->SG;
	unsigned long flags;
	u64bit temp64;
	int i, ddir, sg_index = 0;

	if (c->Request.Type.Direction == XFER_READ)
		ddir = PCI_DMA_FROMDEVICE;
	else
		ddir = PCI_DMA_TODEVICE;

	/* command did not need to be retried */
	/* unmap the DMA mapping for all the scatter gather elements */
	for (i = 0; i < c->Header.SGList; i++) {
		if (curr_sg[sg_index].Ext == CCISS_SG_CHAIN) {
			cciss_unmap_sg_chain_block(h, c);
			/* Point to the next block */
			curr_sg = h->cmd_sg_list[c->cmdindex];
			sg_index = 0;
		}
		temp64.val32.lower = curr_sg[sg_index].Addr.lower;
		temp64.val32.upper = curr_sg[sg_index].Addr.upper;
		pci_unmap_page(h->pdev, temp64.val, curr_sg[sg_index].Len,
				ddir);
		++sg_index;
	}

	dev_dbg(&h->pdev->dev, "Done with %p\n", rq);

	/* set the residual count for pc requests */
	if (rq->cmd_type == REQ_TYPE_BLOCK_PC)
		rq->resid_len = c->err_info->ResidualCnt;

	blk_end_request_all(rq, (rq->errors == 0) ? 0 : -EIO);

	spin_lock_irqsave(&h->lock, flags);
	cmd_free(h, c);
	cciss_check_queues(h);
	spin_unlock_irqrestore(&h->lock, flags);
}