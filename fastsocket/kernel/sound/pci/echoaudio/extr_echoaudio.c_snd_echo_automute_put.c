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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct echoaudio {int digital_in_automute; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int set_input_auto_mute (struct echoaudio*,int) ; 
 struct echoaudio* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_echo_automute_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct echoaudio *chip = snd_kcontrol_chip(kcontrol);
	int automute, changed = 0;

	automute = !!ucontrol->value.integer.value[0];
	if (chip->digital_in_automute != automute) {
		spin_lock_irq(&chip->lock);
		changed = set_input_auto_mute(chip, automute);
		spin_unlock_irq(&chip->lock);
		if (changed == 0)
			changed = 1;	/* no errors */
	}
	return changed;
}