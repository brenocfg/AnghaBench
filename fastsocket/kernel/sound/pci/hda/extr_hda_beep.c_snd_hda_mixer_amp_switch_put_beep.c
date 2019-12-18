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
typedef  int u8 ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {long* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hda_codec {struct hda_beep* beep; } ;
struct hda_beep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctl_has_mute (struct snd_kcontrol*) ; 
 int get_amp_channels (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_hda_enable_beep_device (struct hda_codec*,int) ; 
 int snd_hda_mixer_amp_switch_put (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

int snd_hda_mixer_amp_switch_put_beep(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct hda_beep *beep = codec->beep;
	if (beep) {
		u8 chs = get_amp_channels(kcontrol);
		int enable = 0;
		long *valp = ucontrol->value.integer.value;
		if (chs & 1) {
			enable |= *valp;
			valp++;
		}
		if (chs & 2)
			enable |= *valp;
		snd_hda_enable_beep_device(codec, enable);
	}
	if (!ctl_has_mute(kcontrol))
		return 0;
	return snd_hda_mixer_amp_switch_put(kcontrol, ucontrol);
}