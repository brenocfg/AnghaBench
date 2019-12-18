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
struct via_spec {int num_mixers; int /*<<< orphan*/ * mixers; scalar_t__ set_widgets_power_state; } ;
struct hda_codec {struct via_spec* spec; } ;

/* Variables and functions */
 int snd_hda_add_new_ctls (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_gen_build_controls (struct hda_codec*) ; 
 int /*<<< orphan*/  via_pin_power_ctl_enum ; 

__attribute__((used)) static int via_build_controls(struct hda_codec *codec)
{
	struct via_spec *spec = codec->spec;
	int err, i;

	err = snd_hda_gen_build_controls(codec);
	if (err < 0)
		return err;

	if (spec->set_widgets_power_state)
		spec->mixers[spec->num_mixers++] = via_pin_power_ctl_enum;

	for (i = 0; i < spec->num_mixers; i++) {
		err = snd_hda_add_new_ctls(codec, spec->mixers[i]);
		if (err < 0)
			return err;
	}

	return 0;
}