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
struct snd_rawmidi_substream {struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_runtime {unsigned char* buffer; int avail; int buffer_size; size_t hw_ptr; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_rawmidi_transmit_peek(struct snd_rawmidi_substream *substream,
			      unsigned char *buffer, int count)
{
	unsigned long flags;
	int result, count1;
	struct snd_rawmidi_runtime *runtime = substream->runtime;

	if (runtime->buffer == NULL) {
		snd_printd("snd_rawmidi_transmit_peek: output is not active!!!\n");
		return -EINVAL;
	}
	result = 0;
	spin_lock_irqsave(&runtime->lock, flags);
	if (runtime->avail >= runtime->buffer_size) {
		/* warning: lowlevel layer MUST trigger down the hardware */
		goto __skip;
	}
	if (count == 1) {	/* special case, faster code */
		*buffer = runtime->buffer[runtime->hw_ptr];
		result++;
	} else {
		count1 = runtime->buffer_size - runtime->hw_ptr;
		if (count1 > count)
			count1 = count;
		if (count1 > (int)(runtime->buffer_size - runtime->avail))
			count1 = runtime->buffer_size - runtime->avail;
		memcpy(buffer, runtime->buffer + runtime->hw_ptr, count1);
		count -= count1;
		result += count1;
		if (count > 0) {
			if (count > (int)(runtime->buffer_size - runtime->avail - count1))
				count = runtime->buffer_size - runtime->avail - count1;
			memcpy(buffer + count1, runtime->buffer, count);
			result += count;
		}
	}
      __skip:
	spin_unlock_irqrestore(&runtime->lock, flags);
	return result;
}