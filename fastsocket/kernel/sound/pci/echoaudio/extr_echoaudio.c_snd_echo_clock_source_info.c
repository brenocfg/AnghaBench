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
struct TYPE_3__ {size_t items; size_t item; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;
struct echoaudio {size_t num_clock_sources; size_t* clock_source_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 struct echoaudio* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_echo_clock_source_info(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_info *uinfo)
{
	static char *names[8] = {
		"Internal", "Word", "Super", "S/PDIF", "ADAT", "ESync",
		"ESync96", "MTC"
	};
	struct echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->value.enumerated.items = chip->num_clock_sources;
	uinfo->count = 1;
	if (uinfo->value.enumerated.item >= chip->num_clock_sources)
		uinfo->value.enumerated.item = chip->num_clock_sources - 1;
	strcpy(uinfo->value.enumerated.name, names[
			chip->clock_source_list[uinfo->value.enumerated.item]]);
	return 0;
}