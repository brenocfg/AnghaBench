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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hda_gen_spec {int mute_bits; scalar_t__ auto_mute_via_amp; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int get_amp_nid (struct snd_kcontrol*) ; 
 int snd_hda_mixer_amp_switch_put (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int hda_gen_mixer_mute_put(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct hda_gen_spec *spec = codec->spec;

	if (spec->auto_mute_via_amp) {
		hda_nid_t nid = get_amp_nid(kcontrol);
		bool enabled = !((spec->mute_bits >> nid) & 1);
		ucontrol->value.integer.value[0] &= enabled;
		ucontrol->value.integer.value[1] &= enabled;
	}

	return snd_hda_mixer_amp_switch_put(kcontrol, ucontrol);
}