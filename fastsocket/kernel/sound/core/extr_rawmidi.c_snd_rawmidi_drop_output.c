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
struct snd_rawmidi_runtime {int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  avail; scalar_t__ hw_ptr; scalar_t__ appl_ptr; scalar_t__ drain; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_rawmidi_output_trigger (struct snd_rawmidi_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_rawmidi_drop_output(struct snd_rawmidi_substream *substream)
{
	unsigned long flags;
	struct snd_rawmidi_runtime *runtime = substream->runtime;

	snd_rawmidi_output_trigger(substream, 0);
	runtime->drain = 0;
	spin_lock_irqsave(&runtime->lock, flags);
	runtime->appl_ptr = runtime->hw_ptr = 0;
	runtime->avail = runtime->buffer_size;
	spin_unlock_irqrestore(&runtime->lock, flags);
	return 0;
}