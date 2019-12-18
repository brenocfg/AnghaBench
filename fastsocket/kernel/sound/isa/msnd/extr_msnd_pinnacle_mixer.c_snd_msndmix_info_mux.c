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
struct snd_msnd {int /*<<< orphan*/  flags; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {unsigned int items; unsigned int item; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_HAVEDIGITAL ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 struct snd_msnd* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_msndmix_info_mux(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_info *uinfo)
{
	static char *texts[3] = {
		"Analog", "MASS", "SPDIF",
	};
	struct snd_msnd *chip = snd_kcontrol_chip(kcontrol);
	unsigned items = test_bit(F_HAVEDIGITAL, &chip->flags) ? 3 : 2;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.enumerated.items = items;
	if (uinfo->value.enumerated.item >= items)
		uinfo->value.enumerated.item = items - 1;
	strcpy(uinfo->value.enumerated.name,
		texts[uinfo->value.enumerated.item]);
	return 0;
}