#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_6__ {size_t index; } ;
struct TYPE_4__ {int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ id; TYPE_2__ value; } ;
struct echoaudio {int /*<<< orphan*/ ** monitor_gain; } ;

/* Variables and functions */
 size_t num_busses_in (struct echoaudio*) ; 
 struct echoaudio* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_echo_mixer_get(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	struct echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.integer.value[0] =
		chip->monitor_gain[ucontrol->id.index / num_busses_in(chip)]
			[ucontrol->id.index % num_busses_in(chip)];
	return 0;
}