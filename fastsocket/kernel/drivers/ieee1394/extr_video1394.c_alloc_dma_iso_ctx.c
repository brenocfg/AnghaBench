#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ti_ohci {TYPE_1__* host; int /*<<< orphan*/  dev; } ;
struct it_dma_prg {int dummy; } ;
struct TYPE_8__ {int context; } ;
struct dma_iso_ctx {int type; int channel; int num_desc; int frame_size; int buf_size; int last_buffer; int ctx; int nb_cmd; int left_size; unsigned int packet_size; int /*<<< orphan*/  lock; void* next_buffer; void* last_used_cmd; void* buffer_time; void* buffer_prg_assignment; void* buffer_status; TYPE_4__* prg_reg; struct it_dma_prg** it_prg; scalar_t__ cmdPtr; scalar_t__ ctrlClear; scalar_t__ ctrlSet; struct dma_cmd** ir_prg; scalar_t__ ctxMatch; TYPE_2__ iso_tasklet; int /*<<< orphan*/  dma; int /*<<< orphan*/  waitq; int /*<<< orphan*/  link; struct ti_ohci* ohci; } ;
struct dma_cmd {int dummy; } ;
struct TYPE_9__ {scalar_t__ kvirt; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (int /*<<< orphan*/ ,char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ OHCI1394_IsoRcvCommandPtr ; 
 scalar_t__ OHCI1394_IsoRcvContextControlClear ; 
 scalar_t__ OHCI1394_IsoRcvContextControlSet ; 
 scalar_t__ OHCI1394_IsoRcvContextMatch ; 
 scalar_t__ OHCI1394_IsoXmitCommandPtr ; 
 scalar_t__ OHCI1394_IsoXmitContextControlClear ; 
 scalar_t__ OHCI1394_IsoXmitContextControlSet ; 
 int OHCI_ISO_RECEIVE ; 
 int PAGE_ALIGN (int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ dma_prog_region_alloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_prog_region_init (TYPE_4__*) ; 
 scalar_t__ dma_region_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_region_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_dma_iso_ctx (struct dma_iso_ctx*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 TYPE_4__* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci1394_init_iso_tasklet (TYPE_2__*,int,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ ohci1394_register_iso_tasklet (struct ti_ohci*,TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_dma_ir_ctx ; 
 int /*<<< orphan*/  wakeup_dma_it_ctx ; 

__attribute__((used)) static struct dma_iso_ctx *
alloc_dma_iso_ctx(struct ti_ohci *ohci, int type, int num_desc,
		  int buf_size, int channel, unsigned int packet_size)
{
	struct dma_iso_ctx *d;
	int i;

	d = kzalloc(sizeof(*d), GFP_KERNEL);
	if (!d) {
		PRINT(KERN_ERR, ohci->host->id, "Failed to allocate dma_iso_ctx");
		return NULL;
	}

	d->ohci = ohci;
	d->type = type;
	d->channel = channel;
	d->num_desc = num_desc;
	d->frame_size = buf_size;
	d->buf_size = PAGE_ALIGN(buf_size);
	d->last_buffer = -1;
	INIT_LIST_HEAD(&d->link);
	init_waitqueue_head(&d->waitq);

	/* Init the regions for easy cleanup */
	dma_region_init(&d->dma);

	if (dma_region_alloc(&d->dma, (d->num_desc - 1) * d->buf_size, ohci->dev,
			     PCI_DMA_BIDIRECTIONAL)) {
		PRINT(KERN_ERR, ohci->host->id, "Failed to allocate dma buffer");
		free_dma_iso_ctx(d);
		return NULL;
	}

	if (type == OHCI_ISO_RECEIVE)
		ohci1394_init_iso_tasklet(&d->iso_tasklet, type,
					  wakeup_dma_ir_ctx,
					  (unsigned long) d);
	else
		ohci1394_init_iso_tasklet(&d->iso_tasklet, type,
					  wakeup_dma_it_ctx,
					  (unsigned long) d);

	if (ohci1394_register_iso_tasklet(ohci, &d->iso_tasklet) < 0) {
		PRINT(KERN_ERR, ohci->host->id, "no free iso %s contexts",
		      type == OHCI_ISO_RECEIVE ? "receive" : "transmit");
		free_dma_iso_ctx(d);
		return NULL;
	}
	d->ctx = d->iso_tasklet.context;

	d->prg_reg = kmalloc(d->num_desc * sizeof(*d->prg_reg), GFP_KERNEL);
	if (!d->prg_reg) {
		PRINT(KERN_ERR, ohci->host->id, "Failed to allocate ir prg regs");
		free_dma_iso_ctx(d);
		return NULL;
	}
	/* Makes for easier cleanup */
	for (i = 0; i < d->num_desc; i++)
		dma_prog_region_init(&d->prg_reg[i]);

	if (type == OHCI_ISO_RECEIVE) {
		d->ctrlSet = OHCI1394_IsoRcvContextControlSet+32*d->ctx;
		d->ctrlClear = OHCI1394_IsoRcvContextControlClear+32*d->ctx;
		d->cmdPtr = OHCI1394_IsoRcvCommandPtr+32*d->ctx;
		d->ctxMatch = OHCI1394_IsoRcvContextMatch+32*d->ctx;

		d->ir_prg = kzalloc(d->num_desc * sizeof(*d->ir_prg),
				    GFP_KERNEL);

		if (!d->ir_prg) {
			PRINT(KERN_ERR, ohci->host->id, "Failed to allocate dma ir prg");
			free_dma_iso_ctx(d);
			return NULL;
		}

		d->nb_cmd = d->buf_size / PAGE_SIZE + 1;
		d->left_size = (d->frame_size % PAGE_SIZE) ?
			d->frame_size % PAGE_SIZE : PAGE_SIZE;

		for (i = 0;i < d->num_desc; i++) {
			if (dma_prog_region_alloc(&d->prg_reg[i], d->nb_cmd *
						  sizeof(struct dma_cmd), ohci->dev)) {
				PRINT(KERN_ERR, ohci->host->id, "Failed to allocate dma ir prg");
				free_dma_iso_ctx(d);
				return NULL;
			}
			d->ir_prg[i] = (struct dma_cmd *)d->prg_reg[i].kvirt;
		}

	} else {  /* OHCI_ISO_TRANSMIT */
		d->ctrlSet = OHCI1394_IsoXmitContextControlSet+16*d->ctx;
		d->ctrlClear = OHCI1394_IsoXmitContextControlClear+16*d->ctx;
		d->cmdPtr = OHCI1394_IsoXmitCommandPtr+16*d->ctx;

		d->it_prg = kzalloc(d->num_desc * sizeof(*d->it_prg),
				    GFP_KERNEL);

		if (!d->it_prg) {
			PRINT(KERN_ERR, ohci->host->id,
			      "Failed to allocate dma it prg");
			free_dma_iso_ctx(d);
			return NULL;
		}

		d->packet_size = packet_size;

		if (PAGE_SIZE % packet_size || packet_size>4096) {
			PRINT(KERN_ERR, ohci->host->id,
			      "Packet size %d (page_size: %ld) "
			      "not yet supported\n",
			      packet_size, PAGE_SIZE);
			free_dma_iso_ctx(d);
			return NULL;
		}

		d->nb_cmd = d->frame_size / d->packet_size;
		if (d->frame_size % d->packet_size) {
			d->nb_cmd++;
			d->left_size = d->frame_size % d->packet_size;
		} else
			d->left_size = d->packet_size;

		for (i = 0; i < d->num_desc; i++) {
			if (dma_prog_region_alloc(&d->prg_reg[i], d->nb_cmd *
						sizeof(struct it_dma_prg), ohci->dev)) {
				PRINT(KERN_ERR, ohci->host->id, "Failed to allocate dma it prg");
				free_dma_iso_ctx(d);
				return NULL;
			}
			d->it_prg[i] = (struct it_dma_prg *)d->prg_reg[i].kvirt;
		}
	}

	d->buffer_status =
	    kzalloc(d->num_desc * sizeof(*d->buffer_status), GFP_KERNEL);
	d->buffer_prg_assignment =
	    kzalloc(d->num_desc * sizeof(*d->buffer_prg_assignment), GFP_KERNEL);
	d->buffer_time =
	    kzalloc(d->num_desc * sizeof(*d->buffer_time), GFP_KERNEL);
	d->last_used_cmd =
	    kzalloc(d->num_desc * sizeof(*d->last_used_cmd), GFP_KERNEL);
	d->next_buffer =
	    kzalloc(d->num_desc * sizeof(*d->next_buffer), GFP_KERNEL);

	if (!d->buffer_status || !d->buffer_prg_assignment || !d->buffer_time ||
	    !d->last_used_cmd || !d->next_buffer) {
		PRINT(KERN_ERR, ohci->host->id,
		      "Failed to allocate dma_iso_ctx member");
		free_dma_iso_ctx(d);
		return NULL;
	}

        spin_lock_init(&d->lock);

	DBGMSG(ohci->host->id, "Iso %s DMA: %d buffers "
	      "of size %d allocated for a frame size %d, each with %d prgs",
	      (type == OHCI_ISO_RECEIVE) ? "receive" : "transmit",
	      d->num_desc - 1, d->buf_size, d->frame_size, d->nb_cmd);

	return d;
}