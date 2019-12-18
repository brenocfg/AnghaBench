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
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_5__ {int items; int item; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_3__ value; int /*<<< orphan*/  type; } ;
struct snd_akm4xxx {TYPE_1__* adc_info; } ;
struct TYPE_4__ {char** input_names; } ;

/* Variables and functions */
 int AK_GET_SHIFT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 int ak4xxx_capture_num_inputs (struct snd_akm4xxx*,int) ; 
 struct snd_akm4xxx* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int ak4xxx_capture_source_info(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_info *uinfo)
{
	struct snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	int mixer_ch = AK_GET_SHIFT(kcontrol->private_value);
	const char **input_names;
	int  num_names, idx;

	num_names = ak4xxx_capture_num_inputs(ak, mixer_ch);
	if (!num_names)
		return -EINVAL;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.enumerated.items = num_names;
	idx = uinfo->value.enumerated.item;
	if (idx >= num_names)
		return -EINVAL;
	input_names = ak->adc_info[mixer_ch].input_names;
	strncpy(uinfo->value.enumerated.name, input_names[idx],
		sizeof(uinfo->value.enumerated.name));
	return 0;
}