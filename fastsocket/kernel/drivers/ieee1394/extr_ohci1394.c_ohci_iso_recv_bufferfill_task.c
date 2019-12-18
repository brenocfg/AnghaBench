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
typedef  int u16 ;
struct ti_ohci {int dummy; } ;
struct ohci_iso_recv {int nblocks; size_t block_dma; int buf_stride; int block_reader; struct dma_cmd* block; struct ti_ohci* ohci; } ;
struct hpsb_iso {int /*<<< orphan*/  overflows; int /*<<< orphan*/  data_buf; } ;
struct dma_cmd {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (char*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*,unsigned char) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_region_sync_for_cpu (int /*<<< orphan*/ *,int,int) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  ohci_iso_recv_bufferfill_parse (struct hpsb_iso*,struct ohci_iso_recv*) ; 

__attribute__((used)) static void ohci_iso_recv_bufferfill_task(struct hpsb_iso *iso, struct ohci_iso_recv *recv)
{
	int loop;
	struct ti_ohci *ohci = recv->ohci;

	/* loop over all blocks */
	for (loop = 0; loop < recv->nblocks; loop++) {

		/* check block_dma to see if it's done */
		struct dma_cmd *im = &recv->block[recv->block_dma];

		/* check the DMA descriptor for new writes to xferStatus */
		u16 xferstatus = le32_to_cpu(im->status) >> 16;

		/* rescount is the number of bytes *remaining to be written* in the block */
		u16 rescount = le32_to_cpu(im->status) & 0xFFFF;

		unsigned char event = xferstatus & 0x1F;

		if (!event) {
			/* nothing has happened to this block yet */
			break;
		}

		if (event != 0x11) {
			atomic_inc(&iso->overflows);
			PRINT(KERN_ERR,
			      "IR DMA error - OHCI error code 0x%02x\n", event);
		}

		if (rescount != 0) {
			/* the card is still writing to this block;
			   we can't touch it until it's done */
			break;
		}

		/* OK, the block is finished... */

		/* sync our view of the block */
		dma_region_sync_for_cpu(&iso->data_buf, recv->block_dma*recv->buf_stride, recv->buf_stride);

		/* reset the DMA descriptor */
		im->status = recv->buf_stride;

		/* advance block_dma */
		recv->block_dma = (recv->block_dma + 1) % recv->nblocks;

		if ((recv->block_dma+1) % recv->nblocks == recv->block_reader) {
			atomic_inc(&iso->overflows);
			DBGMSG("ISO reception overflow - "
			       "ran out of DMA blocks");
		}
	}

	/* parse any packets that have arrived */
	ohci_iso_recv_bufferfill_parse(iso, recv);
}