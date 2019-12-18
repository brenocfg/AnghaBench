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
struct TYPE_4__ {int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct echoaudio {int input_clock; int num_clock_sources; int* clock_source_list; } ;

/* Variables and functions */
 struct echoaudio* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_echo_clock_source_get(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct echoaudio *chip;
	int i, clock;

	chip = snd_kcontrol_chip(kcontrol);
	clock = chip->input_clock;

	for (i = 0; i < chip->num_clock_sources; i++)
		if (clock == chip->clock_source_list[i])
			ucontrol->value.enumerated.item[0] = i;

	return 0;
}