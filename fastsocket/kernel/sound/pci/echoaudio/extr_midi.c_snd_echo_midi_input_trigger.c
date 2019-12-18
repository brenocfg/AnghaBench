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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct echoaudio {int midi_input_enabled; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct echoaudio* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_midi_input (struct echoaudio*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_echo_midi_input_trigger(struct snd_rawmidi_substream *substream,
					int up)
{
	struct echoaudio *chip = substream->rmidi->private_data;

	if (up != chip->midi_input_enabled) {
		spin_lock_irq(&chip->lock);
		enable_midi_input(chip, up);
		spin_unlock_irq(&chip->lock);
		chip->midi_input_enabled = up;
	}
}