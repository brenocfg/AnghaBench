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
struct snd_emu10k1 {TYPE_1__* card_capabilities; } ;
struct TYPE_5__ {int items; int item; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_3__ value; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {scalar_t__ emu_model; } ;

/* Variables and functions */
 scalar_t__ EMU_MODEL_EMU1616 ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 char** emu1010_src_texts ; 
 char** emu1616_src_texts ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_emu1010_input_output_source_info(struct snd_kcontrol *kcontrol,
						struct snd_ctl_elem_info *uinfo)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	char **items;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	if (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616) {
		uinfo->value.enumerated.items = 49;
		items = emu1616_src_texts;
	} else {
		uinfo->value.enumerated.items = 53;
		items = emu1010_src_texts;
	}
	if (uinfo->value.enumerated.item >= uinfo->value.enumerated.items)
		uinfo->value.enumerated.item =
			uinfo->value.enumerated.items - 1;
	strcpy(uinfo->value.enumerated.name,
	       items[uinfo->value.enumerated.item]);
	return 0;
}