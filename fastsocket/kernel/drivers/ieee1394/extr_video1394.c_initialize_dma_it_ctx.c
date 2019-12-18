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
struct dma_iso_ctx {int flags; int syt_offset; int num_desc; int ctx; int /*<<< orphan*/  ctrlClear; scalar_t__ ohci; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_IsoXmitIntMaskSet ; 
 int /*<<< orphan*/  initialize_dma_it_prg (struct dma_iso_ctx*,int,int) ; 
 int /*<<< orphan*/  ohci1394_stop_context (struct ti_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void initialize_dma_it_ctx(struct dma_iso_ctx *d, int sync_tag,
				  unsigned int syt_offset, int flags)
{
	struct ti_ohci *ohci = (struct ti_ohci *)d->ohci;
	int i;

	d->flags = flags;
	d->syt_offset = (syt_offset == 0 ? 11000 : syt_offset);

	ohci1394_stop_context(ohci, d->ctrlClear, NULL);

	for (i=0;i<d->num_desc;i++)
		initialize_dma_it_prg(d, i, sync_tag);

	/* Set up isoRecvIntMask to generate interrupts */
	reg_write(ohci, OHCI1394_IsoXmitIntMaskSet, 1<<d->ctx);
}