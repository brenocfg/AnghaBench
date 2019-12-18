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
typedef  size_t uint32_t ;
struct audio_in {size_t in_head; int in_tail; int /*<<< orphan*/  wait; int /*<<< orphan*/  dsp_lock; int /*<<< orphan*/  dsp_cnt; int /*<<< orphan*/  in_count; TYPE_1__* in; } ;
struct audio_frame {int /*<<< orphan*/  bytes; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; scalar_t__ data; } ;

/* Variables and functions */
 int FRAME_NUM ; 
 int /*<<< orphan*/  audio_dsp_read_buffer (struct audio_in*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void audio_in_get_dsp_frames(struct audio_in *audio)
{
	struct audio_frame *frame;
	uint32_t index;
	unsigned long flags;

	index = audio->in_head;

	/* XXX check for bogus frame size? */

	frame = (void *) (((char *)audio->in[index].data) - sizeof(*frame));

	spin_lock_irqsave(&audio->dsp_lock, flags);
	audio->in[index].size = frame->bytes;

	audio->in_head = (audio->in_head + 1) & (FRAME_NUM - 1);

	/* If overflow, move the tail index foward. */
	if (audio->in_head == audio->in_tail)
		audio->in_tail = (audio->in_tail + 1) & (FRAME_NUM - 1);
	else
		audio->in_count++;

	audio_dsp_read_buffer(audio, audio->dsp_cnt++);
	spin_unlock_irqrestore(&audio->dsp_lock, flags);

	wake_up(&audio->wait);
}