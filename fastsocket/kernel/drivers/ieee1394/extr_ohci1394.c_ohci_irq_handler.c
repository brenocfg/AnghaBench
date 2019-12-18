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
struct dma_rcv_ctx {int /*<<< orphan*/  task; int /*<<< orphan*/  ctrlClear; scalar_t__ ctrlSet; } ;
struct dma_trm_ctx {int /*<<< orphan*/  task; int /*<<< orphan*/  ctrlClear; scalar_t__ ctrlSet; } ;
struct ti_ohci {int nb_iso_xmit_ctx; int nb_iso_rcv_ctx; int /*<<< orphan*/  event_lock; struct dma_rcv_ctx ar_resp_context; struct dma_rcv_ctx ar_req_context; struct dma_trm_ctx at_resp_context; struct dma_trm_ctx at_req_context; struct hpsb_host* host; scalar_t__ check_busreset; } ;
struct hpsb_host {scalar_t__ in_bus_reset; } ;
typedef  int quadlet_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (char*,...) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LONG_RESET ; 
 scalar_t__ OHCI1394_AsReqRcvCommandPtr ; 
 scalar_t__ OHCI1394_AsReqRcvContextControlSet ; 
 scalar_t__ OHCI1394_AsReqTrCommandPtr ; 
 scalar_t__ OHCI1394_AsReqTrContextControlSet ; 
 scalar_t__ OHCI1394_AsRspRcvCommandPtr ; 
 scalar_t__ OHCI1394_AsRspRcvContextControlSet ; 
 scalar_t__ OHCI1394_AsRspTrCommandPtr ; 
 scalar_t__ OHCI1394_AsRspTrContextControlSet ; 
 scalar_t__ OHCI1394_IntEventClear ; 
 scalar_t__ OHCI1394_IntEventSet ; 
 scalar_t__ OHCI1394_IntMaskClear ; 
 scalar_t__ OHCI1394_IntMaskSet ; 
 scalar_t__ OHCI1394_IsoRcvCommandPtr ; 
 scalar_t__ OHCI1394_IsoRcvContextControlSet ; 
 scalar_t__ OHCI1394_IsoRcvContextMatch ; 
 scalar_t__ OHCI1394_IsoRecvIntEventClear ; 
 scalar_t__ OHCI1394_IsoRecvIntEventSet ; 
 scalar_t__ OHCI1394_IsoXmitCommandPtr ; 
 scalar_t__ OHCI1394_IsoXmitContextControlSet ; 
 scalar_t__ OHCI1394_IsoXmitIntEventClear ; 
 scalar_t__ OHCI1394_IsoXmitIntEventSet ; 
 scalar_t__ OHCI1394_LinkControlSet ; 
 int OHCI1394_LinkControl_CycleMaster ; 
 scalar_t__ OHCI1394_NodeID ; 
 scalar_t__ OHCI1394_PhyReqFilterHiSet ; 
 scalar_t__ OHCI1394_PhyReqFilterLoSet ; 
 int OHCI1394_RQPkt ; 
 int OHCI1394_RSPkt ; 
 int OHCI1394_busReset ; 
 int OHCI1394_cycleInconsistent ; 
 int OHCI1394_cycleTooLong ; 
 int OHCI1394_isochRx ; 
 int OHCI1394_isochTx ; 
 int OHCI1394_postedWriteErr ; 
 int OHCI1394_reqTxComplete ; 
 int OHCI1394_respTxComplete ; 
 int OHCI1394_selfIDComplete ; 
 int OHCI1394_unrecoverableError ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  RESET_BUS ; 
 int /*<<< orphan*/  dma_trm_tasklet (unsigned long) ; 
 int /*<<< orphan*/  handle_selfid (struct ti_ohci*,struct hpsb_host*,int,int) ; 
 int /*<<< orphan*/  hpsb_bus_reset (struct hpsb_host*) ; 
 int /*<<< orphan*/  hpsb_selfid_complete (struct hpsb_host*,int,int) ; 
 int /*<<< orphan*/  ohci1394_stop_context (struct ti_ohci*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ohci_devctl (struct hpsb_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_schedule_iso_tasklets (struct ti_ohci*,int,int) ; 
 scalar_t__ phys_dma ; 
 scalar_t__ printk_ratelimit () ; 
 int reg_read (struct ti_ohci*,scalar_t__) ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static irqreturn_t ohci_irq_handler(int irq, void *dev_id)
{
	quadlet_t event, node_id;
	struct ti_ohci *ohci = (struct ti_ohci *)dev_id;
	struct hpsb_host *host = ohci->host;
	int phyid = -1, isroot = 0;
	unsigned long flags;

	/* Read and clear the interrupt event register.  Don't clear
	 * the busReset event, though. This is done when we get the
	 * selfIDComplete interrupt. */
	spin_lock_irqsave(&ohci->event_lock, flags);
	event = reg_read(ohci, OHCI1394_IntEventClear);
	reg_write(ohci, OHCI1394_IntEventClear, event & ~OHCI1394_busReset);
	spin_unlock_irqrestore(&ohci->event_lock, flags);

	if (!event)
		return IRQ_NONE;

	/* If event is ~(u32)0 cardbus card was ejected.  In this case
	 * we just return, and clean up in the ohci1394_pci_remove
	 * function. */
	if (event == ~(u32) 0) {
		DBGMSG("Device removed.");
		return IRQ_NONE;
	}

	DBGMSG("IntEvent: %08x", event);

	if (event & OHCI1394_unrecoverableError) {
		int ctx;
		PRINT(KERN_ERR, "Unrecoverable error!");

		if (reg_read(ohci, OHCI1394_AsReqTrContextControlSet) & 0x800)
			PRINT(KERN_ERR, "Async Req Tx Context died: "
				"ctrl[%08x] cmdptr[%08x]",
				reg_read(ohci, OHCI1394_AsReqTrContextControlSet),
				reg_read(ohci, OHCI1394_AsReqTrCommandPtr));

		if (reg_read(ohci, OHCI1394_AsRspTrContextControlSet) & 0x800)
			PRINT(KERN_ERR, "Async Rsp Tx Context died: "
				"ctrl[%08x] cmdptr[%08x]",
				reg_read(ohci, OHCI1394_AsRspTrContextControlSet),
				reg_read(ohci, OHCI1394_AsRspTrCommandPtr));

		if (reg_read(ohci, OHCI1394_AsReqRcvContextControlSet) & 0x800)
			PRINT(KERN_ERR, "Async Req Rcv Context died: "
				"ctrl[%08x] cmdptr[%08x]",
				reg_read(ohci, OHCI1394_AsReqRcvContextControlSet),
				reg_read(ohci, OHCI1394_AsReqRcvCommandPtr));

		if (reg_read(ohci, OHCI1394_AsRspRcvContextControlSet) & 0x800)
			PRINT(KERN_ERR, "Async Rsp Rcv Context died: "
				"ctrl[%08x] cmdptr[%08x]",
				reg_read(ohci, OHCI1394_AsRspRcvContextControlSet),
				reg_read(ohci, OHCI1394_AsRspRcvCommandPtr));

		for (ctx = 0; ctx < ohci->nb_iso_xmit_ctx; ctx++) {
			if (reg_read(ohci, OHCI1394_IsoXmitContextControlSet + (16 * ctx)) & 0x800)
				PRINT(KERN_ERR, "Iso Xmit %d Context died: "
					"ctrl[%08x] cmdptr[%08x]", ctx,
					reg_read(ohci, OHCI1394_IsoXmitContextControlSet + (16 * ctx)),
					reg_read(ohci, OHCI1394_IsoXmitCommandPtr + (16 * ctx)));
		}

		for (ctx = 0; ctx < ohci->nb_iso_rcv_ctx; ctx++) {
			if (reg_read(ohci, OHCI1394_IsoRcvContextControlSet + (32 * ctx)) & 0x800)
				PRINT(KERN_ERR, "Iso Recv %d Context died: "
					"ctrl[%08x] cmdptr[%08x] match[%08x]", ctx,
					reg_read(ohci, OHCI1394_IsoRcvContextControlSet + (32 * ctx)),
					reg_read(ohci, OHCI1394_IsoRcvCommandPtr + (32 * ctx)),
					reg_read(ohci, OHCI1394_IsoRcvContextMatch + (32 * ctx)));
		}

		event &= ~OHCI1394_unrecoverableError;
	}
	if (event & OHCI1394_postedWriteErr) {
		PRINT(KERN_ERR, "physical posted write error");
		/* no recovery strategy yet, had to involve protocol drivers */
		event &= ~OHCI1394_postedWriteErr;
	}
	if (event & OHCI1394_cycleTooLong) {
		if(printk_ratelimit())
			PRINT(KERN_WARNING, "isochronous cycle too long");
		else
			DBGMSG("OHCI1394_cycleTooLong");
		reg_write(ohci, OHCI1394_LinkControlSet,
			  OHCI1394_LinkControl_CycleMaster);
		event &= ~OHCI1394_cycleTooLong;
	}
	if (event & OHCI1394_cycleInconsistent) {
		/* We subscribe to the cycleInconsistent event only to
		 * clear the corresponding event bit... otherwise,
		 * isochronous cycleMatch DMA won't work. */
		DBGMSG("OHCI1394_cycleInconsistent");
		event &= ~OHCI1394_cycleInconsistent;
	}
	if (event & OHCI1394_busReset) {
		/* The busReset event bit can't be cleared during the
		 * selfID phase, so we disable busReset interrupts, to
		 * avoid burying the cpu in interrupt requests. */
		spin_lock_irqsave(&ohci->event_lock, flags);
		reg_write(ohci, OHCI1394_IntMaskClear, OHCI1394_busReset);

		if (ohci->check_busreset) {
			int loop_count = 0;

			udelay(10);

			while (reg_read(ohci, OHCI1394_IntEventSet) & OHCI1394_busReset) {
				reg_write(ohci, OHCI1394_IntEventClear, OHCI1394_busReset);

				spin_unlock_irqrestore(&ohci->event_lock, flags);
				udelay(10);
				spin_lock_irqsave(&ohci->event_lock, flags);

				/* The loop counter check is to prevent the driver
				 * from remaining in this state forever. For the
				 * initial bus reset, the loop continues for ever
				 * and the system hangs, until some device is plugged-in
				 * or out manually into a port! The forced reset seems
				 * to solve this problem. This mainly effects nForce2. */
				if (loop_count > 10000) {
					ohci_devctl(host, RESET_BUS, LONG_RESET);
					DBGMSG("Detected bus-reset loop. Forced a bus reset!");
					loop_count = 0;
				}

				loop_count++;
			}
		}
		spin_unlock_irqrestore(&ohci->event_lock, flags);
		if (!host->in_bus_reset) {
			DBGMSG("irq_handler: Bus reset requested");

			/* Subsystem call */
			hpsb_bus_reset(ohci->host);
		}
		event &= ~OHCI1394_busReset;
	}
	if (event & OHCI1394_reqTxComplete) {
		struct dma_trm_ctx *d = &ohci->at_req_context;
		DBGMSG("Got reqTxComplete interrupt "
		       "status=0x%08X", reg_read(ohci, d->ctrlSet));
		if (reg_read(ohci, d->ctrlSet) & 0x800)
			ohci1394_stop_context(ohci, d->ctrlClear,
					      "reqTxComplete");
		else
			dma_trm_tasklet((unsigned long)d);
			//tasklet_schedule(&d->task);
		event &= ~OHCI1394_reqTxComplete;
	}
	if (event & OHCI1394_respTxComplete) {
		struct dma_trm_ctx *d = &ohci->at_resp_context;
		DBGMSG("Got respTxComplete interrupt "
		       "status=0x%08X", reg_read(ohci, d->ctrlSet));
		if (reg_read(ohci, d->ctrlSet) & 0x800)
			ohci1394_stop_context(ohci, d->ctrlClear,
					      "respTxComplete");
		else
			tasklet_schedule(&d->task);
		event &= ~OHCI1394_respTxComplete;
	}
	if (event & OHCI1394_RQPkt) {
		struct dma_rcv_ctx *d = &ohci->ar_req_context;
		DBGMSG("Got RQPkt interrupt status=0x%08X",
		       reg_read(ohci, d->ctrlSet));
		if (reg_read(ohci, d->ctrlSet) & 0x800)
			ohci1394_stop_context(ohci, d->ctrlClear, "RQPkt");
		else
			tasklet_schedule(&d->task);
		event &= ~OHCI1394_RQPkt;
	}
	if (event & OHCI1394_RSPkt) {
		struct dma_rcv_ctx *d = &ohci->ar_resp_context;
		DBGMSG("Got RSPkt interrupt status=0x%08X",
		       reg_read(ohci, d->ctrlSet));
		if (reg_read(ohci, d->ctrlSet) & 0x800)
			ohci1394_stop_context(ohci, d->ctrlClear, "RSPkt");
		else
			tasklet_schedule(&d->task);
		event &= ~OHCI1394_RSPkt;
	}
	if (event & OHCI1394_isochRx) {
		quadlet_t rx_event;

		rx_event = reg_read(ohci, OHCI1394_IsoRecvIntEventSet);
		reg_write(ohci, OHCI1394_IsoRecvIntEventClear, rx_event);
		ohci_schedule_iso_tasklets(ohci, rx_event, 0);
		event &= ~OHCI1394_isochRx;
	}
	if (event & OHCI1394_isochTx) {
		quadlet_t tx_event;

		tx_event = reg_read(ohci, OHCI1394_IsoXmitIntEventSet);
		reg_write(ohci, OHCI1394_IsoXmitIntEventClear, tx_event);
		ohci_schedule_iso_tasklets(ohci, 0, tx_event);
		event &= ~OHCI1394_isochTx;
	}
	if (event & OHCI1394_selfIDComplete) {
		if (host->in_bus_reset) {
			node_id = reg_read(ohci, OHCI1394_NodeID);

			if (!(node_id & 0x80000000)) {
				PRINT(KERN_ERR,
				      "SelfID received, but NodeID invalid "
				      "(probably new bus reset occurred): %08X",
				      node_id);
				goto selfid_not_valid;
			}

			phyid =  node_id & 0x0000003f;
			isroot = (node_id & 0x40000000) != 0;

			DBGMSG("SelfID interrupt received "
			      "(phyid %d, %s)", phyid,
			      (isroot ? "root" : "not root"));

			handle_selfid(ohci, host, phyid, isroot);

			/* Clear the bus reset event and re-enable the
			 * busReset interrupt.  */
			spin_lock_irqsave(&ohci->event_lock, flags);
			reg_write(ohci, OHCI1394_IntEventClear, OHCI1394_busReset);
			reg_write(ohci, OHCI1394_IntMaskSet, OHCI1394_busReset);
			spin_unlock_irqrestore(&ohci->event_lock, flags);

			/* Turn on phys dma reception.
			 *
			 * TODO: Enable some sort of filtering management.
			 */
			if (phys_dma) {
				reg_write(ohci, OHCI1394_PhyReqFilterHiSet,
					  0xffffffff);
				reg_write(ohci, OHCI1394_PhyReqFilterLoSet,
					  0xffffffff);
			}

			DBGMSG("PhyReqFilter=%08x%08x",
			       reg_read(ohci, OHCI1394_PhyReqFilterHiSet),
			       reg_read(ohci, OHCI1394_PhyReqFilterLoSet));

			hpsb_selfid_complete(host, phyid, isroot);
		} else
			PRINT(KERN_ERR,
			      "SelfID received outside of bus reset sequence");

selfid_not_valid:
		event &= ~OHCI1394_selfIDComplete;
	}

	/* Make sure we handle everything, just in case we accidentally
	 * enabled an interrupt that we didn't write a handler for.  */
	if (event)
		PRINT(KERN_ERR, "Unhandled interrupt(s) 0x%08x",
		      event);

	return IRQ_HANDLED;
}