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
struct snd_es18xx {int version; } ;
struct TYPE_3__ {int items; int item; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 struct snd_es18xx* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_es18xx_info_mux(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
	static char *texts4Source[4] = {
		"Mic", "CD", "Line", "Master"
	};
	static char *texts5Source[5] = {
		"Mic", "CD", "Line", "Master", "Mix"
	};
	static char *texts8Source[8] = {
		"Mic", "Mic Master", "CD", "AOUT",
		"Mic1", "Mix", "Line", "Master"
	};
	struct snd_es18xx *chip = snd_kcontrol_chip(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	switch (chip->version) {
	case 0x1868:
	case 0x1878:
		uinfo->value.enumerated.items = 4;
		if (uinfo->value.enumerated.item > 3)
			uinfo->value.enumerated.item = 3;
		strcpy(uinfo->value.enumerated.name, texts4Source[uinfo->value.enumerated.item]);
		break;
	case 0x1887:
	case 0x1888:
		uinfo->value.enumerated.items = 5;
		if (uinfo->value.enumerated.item > 4)
			uinfo->value.enumerated.item = 4;
		strcpy(uinfo->value.enumerated.name, texts5Source[uinfo->value.enumerated.item]);
		break;
	case 0x1869: /* DS somewhat contradictory for 1869: could be be 5 or 8 */
	case 0x1879:
		uinfo->value.enumerated.items = 8;
		if (uinfo->value.enumerated.item > 7)
			uinfo->value.enumerated.item = 7;
		strcpy(uinfo->value.enumerated.name, texts8Source[uinfo->value.enumerated.item]);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}