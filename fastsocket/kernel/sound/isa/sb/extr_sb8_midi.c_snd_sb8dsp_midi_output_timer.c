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
struct TYPE_4__ {scalar_t__ expires; } ;
struct snd_sb {int /*<<< orphan*/  open_lock; TYPE_2__ midi_timer; } ;
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct TYPE_3__ {struct snd_sb* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  snd_sb8dsp_midi_output_write (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_sb8dsp_midi_output_timer(unsigned long data)
{
	struct snd_rawmidi_substream *substream = (struct snd_rawmidi_substream *) data;
	struct snd_sb * chip = substream->rmidi->private_data;
	unsigned long flags;

	spin_lock_irqsave(&chip->open_lock, flags);
	chip->midi_timer.expires = 1 + jiffies;
	add_timer(&chip->midi_timer);
	spin_unlock_irqrestore(&chip->open_lock, flags);	
	snd_sb8dsp_midi_output_write(substream);
}