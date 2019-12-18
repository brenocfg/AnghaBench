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
struct dma_iso_ctx {int flags; int num_desc; int channel; int ctx; int /*<<< orphan*/  ctxMatch; int /*<<< orphan*/  ctrlSet; int /*<<< orphan*/  ctrlClear; scalar_t__ ohci; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_IsoRecvIntMaskSet ; 
 int VIDEO1394_INCLUDE_ISO_HEADERS ; 
 int /*<<< orphan*/  initialize_dma_ir_prg (struct dma_iso_ctx*,int,int) ; 
 int /*<<< orphan*/  ohci1394_stop_context (struct ti_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_ir_status (struct dma_iso_ctx*,int) ; 

__attribute__((used)) static void initialize_dma_ir_ctx(struct dma_iso_ctx *d, int tag, int flags)
{
	struct ti_ohci *ohci = (struct ti_ohci *)d->ohci;
	int i;

	d->flags = flags;

	ohci1394_stop_context(ohci, d->ctrlClear, NULL);

	for (i=0;i<d->num_desc;i++) {
		initialize_dma_ir_prg(d, i, flags);
		reset_ir_status(d, i);
	}

	/* reset the ctrl register */
	reg_write(ohci, d->ctrlClear, 0xf0000000);

	/* Set bufferFill */
	reg_write(ohci, d->ctrlSet, 0x80000000);

	/* Set isoch header */
	if (flags & VIDEO1394_INCLUDE_ISO_HEADERS)
		reg_write(ohci, d->ctrlSet, 0x40000000);

	/* Set the context match register to match on all tags,
	   sync for sync tag, and listen to d->channel */
	reg_write(ohci, d->ctxMatch, 0xf0000000|((tag&0xf)<<8)|d->channel);

	/* Set up isoRecvIntMask to generate interrupts */
	reg_write(ohci, OHCI1394_IsoRecvIntMaskSet, 1<<d->ctx);
}