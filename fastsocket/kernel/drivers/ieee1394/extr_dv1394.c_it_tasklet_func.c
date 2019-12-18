#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct video_card {int ohci_it_ctx; int active_frame; unsigned int n_frames; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  waitq; int /*<<< orphan*/  fasync; int /*<<< orphan*/  dropped_frames; scalar_t__ syt_offset; struct frame** frames; int /*<<< orphan*/  n_clear_frames; int /*<<< orphan*/  ohci_IsoXmitContextControlSet; int /*<<< orphan*/  ohci; int /*<<< orphan*/  ohci_IsoXmitCommandPtr; int /*<<< orphan*/  dma_running; } ;
struct frame {scalar_t__ state; int done; int assigned_timestamp; scalar_t__* frame_end_timestamp; TYPE_2__* cip_syt2; TYPE_1__* cip_syt1; scalar_t__ n_packets; scalar_t__* frame_begin_timestamp; scalar_t__* mid_frame_timestamp; } ;
struct TYPE_4__ {int* b; } ;
struct TYPE_3__ {int* b; } ;

/* Variables and functions */
 scalar_t__ FRAME_READY ; 
 int /*<<< orphan*/  POLL_OUT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  debug_printk (char*) ; 
 int /*<<< orphan*/  frame_reset (struct frame*) ; 
 int /*<<< orphan*/  irq_printk (char*,...) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (scalar_t__) ; 
 int reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void it_tasklet_func(unsigned long data)
{
	int wake = 0;
	struct video_card *video = (struct video_card*) data;

	spin_lock(&video->spinlock);

	if (!video->dma_running)
		goto out;

	irq_printk("ContextControl = %08x, CommandPtr = %08x\n",
	       reg_read(video->ohci, video->ohci_IsoXmitContextControlSet),
	       reg_read(video->ohci, video->ohci_IsoXmitCommandPtr)
	       );


	if ( (video->ohci_it_ctx != -1) &&
	    (reg_read(video->ohci, video->ohci_IsoXmitContextControlSet) & (1 << 10)) ) {

		struct frame *f;
		unsigned int frame, i;


		if (video->active_frame == -1)
			frame = 0;
		else
			frame = video->active_frame;

		/* check all the DMA-able frames */
		for (i = 0; i < video->n_frames; i++, frame = (frame+1) % video->n_frames) {

			irq_printk("IRQ checking frame %d...", frame);
			f = video->frames[frame];
			if (f->state != FRAME_READY) {
				irq_printk("clear, skipping\n");
				/* we don't own this frame */
				continue;
			}

			irq_printk("DMA\n");

			/* check the frame begin semaphore to see if we can free the previous frame */
			if ( *(f->frame_begin_timestamp) ) {
				int prev_frame;
				struct frame *prev_f;



				/* don't reset, need this later *(f->frame_begin_timestamp) = 0; */
				irq_printk("  BEGIN\n");

				prev_frame = frame - 1;
				if (prev_frame == -1)
					prev_frame += video->n_frames;
				prev_f = video->frames[prev_frame];

				/* make sure we can actually garbage collect
				   this frame */
				if ( (prev_f->state == FRAME_READY) &&
				    prev_f->done && (!f->done) )
				{
					frame_reset(prev_f);
					video->n_clear_frames++;
					wake = 1;
					video->active_frame = frame;

					irq_printk("  BEGIN - freeing previous frame %d, new active frame is %d\n", prev_frame, frame);
				} else {
					irq_printk("  BEGIN - can't free yet\n");
				}

				f->done = 1;
			}


			/* see if we need to set the timestamp for the next frame */
			if ( *(f->mid_frame_timestamp) ) {
				struct frame *next_frame;
				u32 begin_ts, ts_cyc, ts_off;

				*(f->mid_frame_timestamp) = 0;

				begin_ts = le32_to_cpu(*(f->frame_begin_timestamp));

				irq_printk("  MIDDLE - first packet was sent at cycle %4u (%2u), assigned timestamp was (%2u) %4u\n",
					   begin_ts & 0x1FFF, begin_ts & 0xF,
					   f->assigned_timestamp >> 12, f->assigned_timestamp & 0xFFF);

				/* prepare next frame and assign timestamp */
				next_frame = video->frames[ (frame+1) % video->n_frames ];

				if (next_frame->state == FRAME_READY) {
					irq_printk("  MIDDLE - next frame is ready, good\n");
				} else {
					debug_printk("dv1394: Underflow! At least one frame has been dropped.\n");
					next_frame = f;
				}

				/* set the timestamp to the timestamp of the last frame sent,
				   plus the length of the last frame sent, plus the syt latency */
				ts_cyc = begin_ts & 0xF;
				/* advance one frame, plus syt latency (typically 2-3) */
				ts_cyc += f->n_packets + video->syt_offset ;

				ts_off = 0;

				ts_cyc += ts_off/3072;
				ts_off %= 3072;

				next_frame->assigned_timestamp = ((ts_cyc&0xF) << 12) + ts_off;
				if (next_frame->cip_syt1) {
					next_frame->cip_syt1->b[6] = next_frame->assigned_timestamp >> 8;
					next_frame->cip_syt1->b[7] = next_frame->assigned_timestamp & 0xFF;
				}
				if (next_frame->cip_syt2) {
					next_frame->cip_syt2->b[6] = next_frame->assigned_timestamp >> 8;
					next_frame->cip_syt2->b[7] = next_frame->assigned_timestamp & 0xFF;
				}

			}

			/* see if the frame looped */
			if ( *(f->frame_end_timestamp) ) {

				*(f->frame_end_timestamp) = 0;

				debug_printk("  END - the frame looped at least once\n");

				video->dropped_frames++;
			}

		} /* for (each frame) */
	}

	if (wake) {
		kill_fasync(&video->fasync, SIGIO, POLL_OUT);

		/* wake readers/writers/ioctl'ers */
		wake_up_interruptible(&video->waitq);
	}

out:
	spin_unlock(&video->spinlock);
}