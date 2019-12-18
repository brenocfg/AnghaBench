#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct video_card {int ohci_it_ctx; int ohci_ir_ctx; int channel; scalar_t__ packet_buf_size; int /*<<< orphan*/  packet_buf; scalar_t__ dv_buf_size; int /*<<< orphan*/  dv_buf; scalar_t__ n_frames; int /*<<< orphan*/ ** frames; TYPE_1__* ohci; int /*<<< orphan*/  ir_tasklet; scalar_t__ ohci_IsoRcvContextMatch; scalar_t__ ohci_IsoRcvCommandPtr; scalar_t__ ohci_IsoRcvContextControlClear; scalar_t__ ohci_IsoRcvContextControlSet; int /*<<< orphan*/  it_tasklet; scalar_t__ ohci_IsoXmitCommandPtr; scalar_t__ ohci_IsoXmitContextControlClear; scalar_t__ ohci_IsoXmitContextControlSet; } ;
struct TYPE_3__ {int ISO_channel_usage; int /*<<< orphan*/  IR_channel_lock; } ;

/* Variables and functions */
 int DV1394_MAX_FRAMES ; 
 int /*<<< orphan*/  OHCI1394_IsoRecvIntMaskClear ; 
 int /*<<< orphan*/  OHCI1394_IsoXmitIntMaskClear ; 
 int /*<<< orphan*/  debug_printk (char*,...) ; 
 int /*<<< orphan*/  dma_region_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci1394_unregister_iso_tasklet (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_write (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stop_dma (struct video_card*) ; 

__attribute__((used)) static void do_dv1394_shutdown(struct video_card *video, int free_dv_buf)
{
	int i;

	debug_printk("dv1394: shutdown...\n");

	/* stop DMA if in progress */
	stop_dma(video);

	/* release the DMA contexts */
	if (video->ohci_it_ctx != -1) {
		video->ohci_IsoXmitContextControlSet = 0;
		video->ohci_IsoXmitContextControlClear = 0;
		video->ohci_IsoXmitCommandPtr = 0;

		/* disable interrupts for IT context */
		reg_write(video->ohci, OHCI1394_IsoXmitIntMaskClear, (1 << video->ohci_it_ctx));

		/* remove tasklet */
		ohci1394_unregister_iso_tasklet(video->ohci, &video->it_tasklet);
		debug_printk("dv1394: IT context %d released\n", video->ohci_it_ctx);
		video->ohci_it_ctx = -1;
	}

	if (video->ohci_ir_ctx != -1) {
		video->ohci_IsoRcvContextControlSet = 0;
		video->ohci_IsoRcvContextControlClear = 0;
		video->ohci_IsoRcvCommandPtr = 0;
		video->ohci_IsoRcvContextMatch = 0;

		/* disable interrupts for IR context */
		reg_write(video->ohci, OHCI1394_IsoRecvIntMaskClear, (1 << video->ohci_ir_ctx));

		/* remove tasklet */
		ohci1394_unregister_iso_tasklet(video->ohci, &video->ir_tasklet);
		debug_printk("dv1394: IR context %d released\n", video->ohci_ir_ctx);
		video->ohci_ir_ctx = -1;
	}

	/* release the ISO channel */
	if (video->channel != -1) {
		u64 chan_mask;
		unsigned long flags;

		chan_mask = (u64)1 << video->channel;

		spin_lock_irqsave(&video->ohci->IR_channel_lock, flags);
		video->ohci->ISO_channel_usage &= ~(chan_mask);
		spin_unlock_irqrestore(&video->ohci->IR_channel_lock, flags);

		video->channel = -1;
	}

	/* free the frame structs */
	for (i = 0; i < DV1394_MAX_FRAMES; i++) {
		if (video->frames[i])
			frame_delete(video->frames[i]);
		video->frames[i] = NULL;
	}

	video->n_frames = 0;

	/* we can't free the DMA buffer unless it is guaranteed that
	   no more user-space mappings exist */

	if (free_dv_buf) {
		dma_region_free(&video->dv_buf);
		video->dv_buf_size = 0;
	}

	/* free packet buffer */
	dma_region_free(&video->packet_buf);
	video->packet_buf_size = 0;

	debug_printk("dv1394: shutdown OK\n");
}