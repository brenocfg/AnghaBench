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
struct vx_core {scalar_t__ type; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int items; int item; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 scalar_t__ VX_TYPE_VXPOCKET ; 
 struct vx_core* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vx_audio_src_info(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
	static char *texts_mic[3] = {
		"Digital", "Line", "Mic"
	};
	static char *texts_vx2[2] = {
		"Digital", "Analog"
	};
	struct vx_core *chip = snd_kcontrol_chip(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	if (chip->type >= VX_TYPE_VXPOCKET) {
		uinfo->value.enumerated.items = 3;
		if (uinfo->value.enumerated.item > 2)
			uinfo->value.enumerated.item = 2;
		strcpy(uinfo->value.enumerated.name,
		       texts_mic[uinfo->value.enumerated.item]);
	} else {
		uinfo->value.enumerated.items = 2;
		if (uinfo->value.enumerated.item > 1)
			uinfo->value.enumerated.item = 1;
		strcpy(uinfo->value.enumerated.name,
		       texts_vx2[uinfo->value.enumerated.item]);
	}
	return 0;
}