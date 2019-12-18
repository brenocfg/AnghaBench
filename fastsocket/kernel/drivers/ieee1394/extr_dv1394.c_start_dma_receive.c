#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct video_card {int first_run; int first_clear_frame; int channel; int dma_running; int /*<<< orphan*/  ohci_IsoRcvContextControlSet; int /*<<< orphan*/  ohci; TYPE_1__** frames; int /*<<< orphan*/  ohci_IsoRcvCommandPtr; int /*<<< orphan*/  ohci_IsoRcvContextMatch; int /*<<< orphan*/  ohci_IsoRcvContextControlClear; scalar_t__ active_frame; scalar_t__ current_packet; scalar_t__ n_clear_frames; } ;
struct TYPE_2__ {int descriptor_pool_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_printk (char*,...) ; 
 int /*<<< orphan*/  flush_pci_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void start_dma_receive(struct video_card *video)
{
	if (video->first_run == 1) {
		video->first_run = 0;

		/* start DMA once all of the frames are READY */
		video->n_clear_frames = 0;
		video->first_clear_frame = -1;
		video->current_packet = 0;
		video->active_frame = 0;

		/* reset iso recv control register */
		reg_write(video->ohci, video->ohci_IsoRcvContextControlClear, 0xFFFFFFFF);
		wmb();

		/* clear bufferFill, set isochHeader and speed (0=100) */
		reg_write(video->ohci, video->ohci_IsoRcvContextControlSet, 0x40000000);

		/* match on all tags, listen on channel */
		reg_write(video->ohci, video->ohci_IsoRcvContextMatch, 0xf0000000 | video->channel);

		/* address and first descriptor block + Z=1 */
		reg_write(video->ohci, video->ohci_IsoRcvCommandPtr,
			  video->frames[0]->descriptor_pool_dma | 1); /* Z=1 */
		wmb();

		video->dma_running = 1;

		/* run */
		reg_write(video->ohci, video->ohci_IsoRcvContextControlSet, 0x8000);
		flush_pci_write(video->ohci);

		debug_printk("dv1394: DMA started\n");

#if DV1394_DEBUG_LEVEL >= 2
		{
			int i;

			for (i = 0; i < 1000; ++i) {
				mdelay(1);
				if (reg_read(video->ohci, video->ohci_IsoRcvContextControlSet) & (1 << 10)) {
					printk("DMA ACTIVE after %d msec\n", i);
					break;
				}
			}
			if ( reg_read(video->ohci, video->ohci_IsoRcvContextControlSet) &  (1 << 11) ) {
				printk("DEAD, event = %x\n",
					   reg_read(video->ohci, video->ohci_IsoRcvContextControlSet) & 0x1F);
			} else
				printk("RUNNING!\n");
		}
#endif
	} else if ( reg_read(video->ohci, video->ohci_IsoRcvContextControlSet) &  (1 << 11) ) {
		debug_printk("DEAD, event = %x\n",
			     reg_read(video->ohci, video->ohci_IsoRcvContextControlSet) & 0x1F);

		/* wake */
		reg_write(video->ohci, video->ohci_IsoRcvContextControlSet, (1 << 12));
	}
}