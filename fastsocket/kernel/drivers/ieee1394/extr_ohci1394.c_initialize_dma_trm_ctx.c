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
struct ti_ohci {int dummy; } ;
struct dma_trm_ctx {scalar_t__ type; int ctx; int /*<<< orphan*/  pending_list; int /*<<< orphan*/  fifo_list; int /*<<< orphan*/ * branchAddrPtr; int /*<<< orphan*/  num_desc; int /*<<< orphan*/  free_prgs; scalar_t__ sent_ind; scalar_t__ prg_ind; int /*<<< orphan*/  ctrlClear; scalar_t__ ohci; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (char*,int) ; 
 scalar_t__ DMA_CTX_ISO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OHCI1394_IsoXmitIntMaskSet ; 
 int /*<<< orphan*/  ohci1394_stop_context (struct ti_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void initialize_dma_trm_ctx(struct dma_trm_ctx *d)
{
	struct ti_ohci *ohci = (struct ti_ohci*)(d->ohci);

	/* Stop the context */
	ohci1394_stop_context(ohci, d->ctrlClear, NULL);

        d->prg_ind = 0;
	d->sent_ind = 0;
	d->free_prgs = d->num_desc;
        d->branchAddrPtr = NULL;
	INIT_LIST_HEAD(&d->fifo_list);
	INIT_LIST_HEAD(&d->pending_list);

	if (d->type == DMA_CTX_ISO) {
		/* enable interrupts */
		reg_write(ohci, OHCI1394_IsoXmitIntMaskSet, 1 << d->ctx);
	}

	DBGMSG("Transmit DMA ctx=%d initialized", d->ctx);
}