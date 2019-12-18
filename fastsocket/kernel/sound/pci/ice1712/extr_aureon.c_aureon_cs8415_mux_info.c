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
struct TYPE_4__ {scalar_t__ subvendor; } ;
struct snd_ice1712 {TYPE_1__ eeprom; } ;
struct TYPE_5__ {int items; int item; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_3__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 scalar_t__ VT1724_SUBDEVICE_PRODIGY71 ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const* const) ; 

__attribute__((used)) static int aureon_cs8415_mux_info(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	static const char * const aureon_texts[] = {
		"CD",		/* RXP0 */
		"Optical"	/* RXP1 */
	};
	static const char * const prodigy_texts[] = {
		"CD",
		"Coax"
	};
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.enumerated.items = 2;
	if (uinfo->value.enumerated.item >= uinfo->value.enumerated.items)
		uinfo->value.enumerated.item = uinfo->value.enumerated.items - 1;
	if (ice->eeprom.subvendor == VT1724_SUBDEVICE_PRODIGY71)
		strcpy(uinfo->value.enumerated.name, prodigy_texts[uinfo->value.enumerated.item]);
	else
		strcpy(uinfo->value.enumerated.name, aureon_texts[uinfo->value.enumerated.item]);
	return 0;
}