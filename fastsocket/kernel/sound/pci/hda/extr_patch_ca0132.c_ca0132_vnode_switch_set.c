#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_kcontrol {unsigned long private_value; } ;
struct snd_ctl_elem_value {int dummy; } ;
struct hda_codec {int /*<<< orphan*/  control_mutex; struct ca0132_spec* spec; } ;
struct ca0132_spec {int* vnode_lswitch; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 unsigned long HDA_COMPOSE_AMP_VAL (scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 size_t VNID_AMIC1_ASEL ; 
 scalar_t__ VNID_AMIC1_SEL ; 
 size_t VNID_HP_ASEL ; 
 scalar_t__ VNID_HP_SEL ; 
 size_t VNODE_START_NID ; 
 int ca0132_is_vnode_effective (struct hda_codec*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ca0132_select_mic (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_select_out (struct hda_codec*) ; 
 int get_amp_channels (struct snd_kcontrol*) ; 
 int get_amp_direction (struct snd_kcontrol*) ; 
 scalar_t__ get_amp_nid (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_hda_mixer_amp_switch_put (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int ca0132_vnode_switch_set(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = get_amp_nid(kcontrol);
	hda_nid_t shared_nid = 0;
	bool effective;
	int ret = 0;
	struct ca0132_spec *spec = codec->spec;
	int auto_jack;

	if (nid == VNID_HP_SEL) {
		auto_jack =
			spec->vnode_lswitch[VNID_HP_ASEL - VNODE_START_NID];
		if (!auto_jack)
			ca0132_select_out(codec);
		return 1;
	}

	if (nid == VNID_AMIC1_SEL) {
		auto_jack =
			spec->vnode_lswitch[VNID_AMIC1_ASEL - VNODE_START_NID];
		if (!auto_jack)
			ca0132_select_mic(codec);
		return 1;
	}

	if (nid == VNID_HP_ASEL) {
		ca0132_select_out(codec);
		return 1;
	}

	if (nid == VNID_AMIC1_ASEL) {
		ca0132_select_mic(codec);
		return 1;
	}

	/* if effective conditions, then update hw immediately. */
	effective = ca0132_is_vnode_effective(codec, nid, &shared_nid);
	if (effective) {
		int dir = get_amp_direction(kcontrol);
		int ch = get_amp_channels(kcontrol);
		unsigned long pval;

		mutex_lock(&codec->control_mutex);
		pval = kcontrol->private_value;
		kcontrol->private_value = HDA_COMPOSE_AMP_VAL(shared_nid, ch,
								0, dir);
		ret = snd_hda_mixer_amp_switch_put(kcontrol, ucontrol);
		kcontrol->private_value = pval;
		mutex_unlock(&codec->control_mutex);
	}

	return ret;
}