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
struct snd_rawmidi_substream {scalar_t__ bytes; int /*<<< orphan*/  opened; struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_runtime {unsigned char* buffer; int avail; int buffer_size; int hw_ptr; int /*<<< orphan*/  lock; int /*<<< orphan*/  sleep; int /*<<< orphan*/  tasklet; scalar_t__ event; scalar_t__ xruns; } ;

/* Variables and functions */
 int EBADFD ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 scalar_t__ snd_rawmidi_ready (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int snd_rawmidi_receive(struct snd_rawmidi_substream *substream,
			const unsigned char *buffer, int count)
{
	unsigned long flags;
	int result = 0, count1;
	struct snd_rawmidi_runtime *runtime = substream->runtime;

	if (!substream->opened)
		return -EBADFD;
	if (runtime->buffer == NULL) {
		snd_printd("snd_rawmidi_receive: input is not active!!!\n");
		return -EINVAL;
	}
	spin_lock_irqsave(&runtime->lock, flags);
	if (count == 1) {	/* special case, faster code */
		substream->bytes++;
		if (runtime->avail < runtime->buffer_size) {
			runtime->buffer[runtime->hw_ptr++] = buffer[0];
			runtime->hw_ptr %= runtime->buffer_size;
			runtime->avail++;
			result++;
		} else {
			runtime->xruns++;
		}
	} else {
		substream->bytes += count;
		count1 = runtime->buffer_size - runtime->hw_ptr;
		if (count1 > count)
			count1 = count;
		if (count1 > (int)(runtime->buffer_size - runtime->avail))
			count1 = runtime->buffer_size - runtime->avail;
		memcpy(runtime->buffer + runtime->hw_ptr, buffer, count1);
		runtime->hw_ptr += count1;
		runtime->hw_ptr %= runtime->buffer_size;
		runtime->avail += count1;
		count -= count1;
		result += count1;
		if (count > 0) {
			buffer += count1;
			count1 = count;
			if (count1 > (int)(runtime->buffer_size - runtime->avail)) {
				count1 = runtime->buffer_size - runtime->avail;
				runtime->xruns += count - count1;
			}
			if (count1 > 0) {
				memcpy(runtime->buffer, buffer, count1);
				runtime->hw_ptr = count1;
				runtime->avail += count1;
				result += count1;
			}
		}
	}
	if (result > 0) {
		if (runtime->event)
			tasklet_schedule(&runtime->tasklet);
		else if (snd_rawmidi_ready(substream))
			wake_up(&runtime->sleep);
	}
	spin_unlock_irqrestore(&runtime->lock, flags);
	return result;
}