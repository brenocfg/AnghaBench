#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ti_ohci {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int context; } ;
struct TYPE_8__ {scalar_t__ kvirt; } ;
struct ohci_iso_recv {int task_active; scalar_t__ dma_mode; int buf_stride; int nblocks; int block_irq_interval; struct ti_ohci* ohci; scalar_t__ ContextMatch; scalar_t__ CommandPtr; scalar_t__ ContextControlClear; scalar_t__ ContextControlSet; TYPE_2__ task; TYPE_4__ prog; struct dma_cmd* block; scalar_t__ dma_offset; scalar_t__ block_dma; scalar_t__ released_bytes; scalar_t__ block_reader; } ;
struct hpsb_iso {int irq_interval; scalar_t__ dma_mode; int channel; int buf_size; int buf_packets; struct ohci_iso_recv* hostdata; TYPE_1__* host; } ;
struct dma_cmd {int dummy; } ;
struct TYPE_6__ {struct ti_ohci* hostdata; } ;

/* Variables and functions */
 scalar_t__ BUFFER_FILL_MODE ; 
 int /*<<< orphan*/  DBGMSG (char*,...) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HPSB_ISO_DMA_OLD_ABI ; 
 scalar_t__ HPSB_ISO_DMA_PACKET_PER_BUFFER ; 
 int /*<<< orphan*/  OHCI1394_IRMultiChanMaskHiClear ; 
 int /*<<< orphan*/  OHCI1394_IRMultiChanMaskLoClear ; 
 scalar_t__ OHCI1394_IsoRcvCommandPtr ; 
 scalar_t__ OHCI1394_IsoRcvContextControlClear ; 
 scalar_t__ OHCI1394_IsoRcvContextControlSet ; 
 scalar_t__ OHCI1394_IsoRcvContextMatch ; 
 int /*<<< orphan*/  OHCI_ISO_MULTICHANNEL_RECEIVE ; 
 int /*<<< orphan*/  OHCI_ISO_RECEIVE ; 
 scalar_t__ PACKET_PER_BUFFER_MODE ; 
 int PAGE_SIZE ; 
 scalar_t__ dma_prog_region_alloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_prog_region_init (TYPE_4__*) ; 
 struct ohci_iso_recv* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci1394_init_iso_tasklet (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ ohci1394_register_iso_tasklet (struct ti_ohci*,TYPE_2__*) ; 
 int /*<<< orphan*/  ohci_iso_recv_program (struct hpsb_iso*) ; 
 int /*<<< orphan*/  ohci_iso_recv_shutdown (struct hpsb_iso*) ; 
 int /*<<< orphan*/  ohci_iso_recv_task ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ohci_iso_recv_init(struct hpsb_iso *iso)
{
	struct ti_ohci *ohci = iso->host->hostdata;
	struct ohci_iso_recv *recv;
	int ctx;
	int ret = -ENOMEM;

	recv = kmalloc(sizeof(*recv), GFP_KERNEL);
	if (!recv)
		return -ENOMEM;

	iso->hostdata = recv;
	recv->ohci = ohci;
	recv->task_active = 0;
	dma_prog_region_init(&recv->prog);
	recv->block = NULL;

	/* use buffer-fill mode, unless irq_interval is 1
	   (note: multichannel requires buffer-fill) */

	if (((iso->irq_interval == 1 && iso->dma_mode == HPSB_ISO_DMA_OLD_ABI) ||
	     iso->dma_mode == HPSB_ISO_DMA_PACKET_PER_BUFFER) && iso->channel != -1) {
		recv->dma_mode = PACKET_PER_BUFFER_MODE;
	} else {
		recv->dma_mode = BUFFER_FILL_MODE;
	}

	/* set nblocks, buf_stride, block_irq_interval */

	if (recv->dma_mode == BUFFER_FILL_MODE) {
		recv->buf_stride = PAGE_SIZE;

		/* one block per page of data in the DMA buffer, minus the final guard page */
		recv->nblocks = iso->buf_size/PAGE_SIZE - 1;
		if (recv->nblocks < 3) {
			DBGMSG("ohci_iso_recv_init: DMA buffer too small");
			goto err;
		}

		/* iso->irq_interval is in packets - translate that to blocks */
		if (iso->irq_interval == 1)
			recv->block_irq_interval = 1;
		else
			recv->block_irq_interval = iso->irq_interval *
							((recv->nblocks+1)/iso->buf_packets);
		if (recv->block_irq_interval*4 > recv->nblocks)
			recv->block_irq_interval = recv->nblocks/4;
		if (recv->block_irq_interval < 1)
			recv->block_irq_interval = 1;

	} else {
		int max_packet_size;

		recv->nblocks = iso->buf_packets;
		recv->block_irq_interval = iso->irq_interval;
		if (recv->block_irq_interval * 4 > iso->buf_packets)
			recv->block_irq_interval = iso->buf_packets / 4;
		if (recv->block_irq_interval < 1)
		recv->block_irq_interval = 1;

		/* choose a buffer stride */
		/* must be a power of 2, and <= PAGE_SIZE */

		max_packet_size = iso->buf_size / iso->buf_packets;

		for (recv->buf_stride = 8; recv->buf_stride < max_packet_size;
		    recv->buf_stride *= 2);

		if (recv->buf_stride*iso->buf_packets > iso->buf_size ||
		   recv->buf_stride > PAGE_SIZE) {
			/* this shouldn't happen, but anyway... */
			DBGMSG("ohci_iso_recv_init: problem choosing a buffer stride");
			goto err;
		}
	}

	recv->block_reader = 0;
	recv->released_bytes = 0;
	recv->block_dma = 0;
	recv->dma_offset = 0;

	/* size of DMA program = one descriptor per block */
	if (dma_prog_region_alloc(&recv->prog,
				 sizeof(struct dma_cmd) * recv->nblocks,
				 recv->ohci->dev))
		goto err;

	recv->block = (struct dma_cmd*) recv->prog.kvirt;

	ohci1394_init_iso_tasklet(&recv->task,
				  iso->channel == -1 ? OHCI_ISO_MULTICHANNEL_RECEIVE :
				                       OHCI_ISO_RECEIVE,
				  ohci_iso_recv_task, (unsigned long) iso);

	if (ohci1394_register_iso_tasklet(recv->ohci, &recv->task) < 0) {
		ret = -EBUSY;
		goto err;
	}

	recv->task_active = 1;

	/* recv context registers are spaced 32 bytes apart */
	ctx = recv->task.context;
	recv->ContextControlSet = OHCI1394_IsoRcvContextControlSet + 32 * ctx;
	recv->ContextControlClear = OHCI1394_IsoRcvContextControlClear + 32 * ctx;
	recv->CommandPtr = OHCI1394_IsoRcvCommandPtr + 32 * ctx;
	recv->ContextMatch = OHCI1394_IsoRcvContextMatch + 32 * ctx;

	if (iso->channel == -1) {
		/* clear multi-channel selection mask */
		reg_write(recv->ohci, OHCI1394_IRMultiChanMaskHiClear, 0xFFFFFFFF);
		reg_write(recv->ohci, OHCI1394_IRMultiChanMaskLoClear, 0xFFFFFFFF);
	}

	/* write the DMA program */
	ohci_iso_recv_program(iso);

	DBGMSG("ohci_iso_recv_init: %s mode, DMA buffer is %lu pages"
	       " (%u bytes), using %u blocks, buf_stride %u, block_irq_interval %d",
	       recv->dma_mode == BUFFER_FILL_MODE ?
	       "buffer-fill" : "packet-per-buffer",
	       iso->buf_size/PAGE_SIZE, iso->buf_size,
	       recv->nblocks, recv->buf_stride, recv->block_irq_interval);

	return 0;

err:
	ohci_iso_recv_shutdown(iso);
	return ret;
}