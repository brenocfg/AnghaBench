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
struct buffer {int used; } ;
struct audio {int out_needed; int out_tail; int /*<<< orphan*/  dsp_lock; struct buffer* out; int /*<<< orphan*/  write_wait; scalar_t__ wflush; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  audplay_dsp_send_data_avail (struct audio*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void audplay_send_data(struct audio *audio, unsigned needed)
{
	struct buffer *frame;
	unsigned long flags;

	spin_lock_irqsave(&audio->dsp_lock, flags);
	if (!audio->running)
		goto done;

	if (audio->wflush) {
		audio->out_needed = 1;
		goto done;
	}

	if (needed && !audio->wflush) {
		/* We were called from the callback because the DSP
		 * requested more data.  Note that the DSP does want
		 * more data, and if a buffer was in-flight, mark it
		 * as available (since the DSP must now be done with
		 * it).
		 */
		audio->out_needed = 1;
		frame = audio->out + audio->out_tail;
		if (frame->used == 0xffffffff) {
		  dprintk("frame %d free\n", audio->out_tail);
		  frame->used = 0;
		  audio->out_tail ^= 1;
		  wake_up(&audio->write_wait);
		}
	}

	if (audio->out_needed) {
		/* If the DSP currently wants data and we have a
		 * buffer available, we will send it and reset
		 * the needed flag.  We'll mark the buffer as in-flight
		 * so that it won't be recycled until the next buffer
		 * is requested
		 */

		frame = audio->out + audio->out_tail;
		if (frame->used) {
		  BUG_ON(frame->used == 0xffffffff);
		  dprintk("frame %d busy\n", audio->out_tail);
		  audplay_dsp_send_data_avail(audio, audio->out_tail,
					      frame->used);
		  frame->used = 0xffffffff;
		  audio->out_needed = 0;
		}
	}
done:
	spin_unlock_irqrestore(&audio->dsp_lock, flags);
}