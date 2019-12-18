#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct TYPE_5__ {unsigned long data; int /*<<< orphan*/  (* function ) (unsigned long) ;} ;
struct echoaudio {int tinuse; int /*<<< orphan*/  midi_full; int /*<<< orphan*/  lock; TYPE_2__ timer; } ;
struct TYPE_4__ {struct echoaudio* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_MID (char*) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  snd_echo_midi_output_write (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_echo_midi_output_trigger(struct snd_rawmidi_substream *substream,
					 int up)
{
	struct echoaudio *chip = substream->rmidi->private_data;

	DE_MID(("snd_echo_midi_output_trigger(%d)\n", up));
	spin_lock_irq(&chip->lock);
	if (up) {
		if (!chip->tinuse) {
			init_timer(&chip->timer);
			chip->timer.function = snd_echo_midi_output_write;
			chip->timer.data = (unsigned long)chip;
			chip->tinuse = 1;
		}
	} else {
		if (chip->tinuse) {
			chip->tinuse = 0;
			spin_unlock_irq(&chip->lock);
			del_timer_sync(&chip->timer);
			DE_MID(("Timer removed\n"));
			return;
		}
	}
	spin_unlock_irq(&chip->lock);

	if (up && !chip->midi_full)
		snd_echo_midi_output_write((unsigned long)chip);
}