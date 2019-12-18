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
struct snd_kcontrol_new {scalar_t__ name; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int num_mixers; scalar_t__ beep_amp; int /*<<< orphan*/ * mixers; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_BUILD ; 
 struct snd_kcontrol_new* alc_beep_mixer ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new const*,struct hda_codec*) ; 
 int snd_hda_add_new_ctls (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_ctl_add (struct hda_codec*,int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 int snd_hda_gen_build_controls (struct hda_codec*) ; 

__attribute__((used)) static int alc_build_controls(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;
	int i, err;

	err = snd_hda_gen_build_controls(codec);
	if (err < 0)
		return err;

	for (i = 0; i < spec->num_mixers; i++) {
		err = snd_hda_add_new_ctls(codec, spec->mixers[i]);
		if (err < 0)
			return err;
	}

#ifdef CONFIG_SND_HDA_INPUT_BEEP
	/* create beep controls if needed */
	if (spec->beep_amp) {
		const struct snd_kcontrol_new *knew;
		for (knew = alc_beep_mixer; knew->name; knew++) {
			struct snd_kcontrol *kctl;
			kctl = snd_ctl_new1(knew, codec);
			if (!kctl)
				return -ENOMEM;
			kctl->private_value = spec->beep_amp;
			err = snd_hda_ctl_add(codec, 0, kctl);
			if (err < 0)
				return err;
		}
	}
#endif

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_BUILD);
	return 0;
}