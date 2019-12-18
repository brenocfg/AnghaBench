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
struct TYPE_4__ {unsigned int* item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  line_out_type; } ;
struct hda_gen_spec {unsigned int aamix_mode; int /*<<< orphan*/ * aamix_out_paths; int /*<<< orphan*/ * speaker_paths; int /*<<< orphan*/ * hp_paths; TYPE_3__ autocfg; int /*<<< orphan*/ * out_paths; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_PIN_HP_OUT ; 
 int /*<<< orphan*/  AUTO_PIN_SPEAKER_OUT ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  update_aamix_paths (struct hda_codec*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int loopback_mixing_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct hda_gen_spec *spec = codec->spec;
	unsigned int val = ucontrol->value.enumerated.item[0];

	if (val == spec->aamix_mode)
		return 0;
	spec->aamix_mode = val;
	update_aamix_paths(codec, val, spec->out_paths[0],
			   spec->aamix_out_paths[0],
			   spec->autocfg.line_out_type);
	update_aamix_paths(codec, val, spec->hp_paths[0],
			   spec->aamix_out_paths[1],
			   AUTO_PIN_HP_OUT);
	update_aamix_paths(codec, val, spec->speaker_paths[0],
			   spec->aamix_out_paths[2],
			   AUTO_PIN_SPEAKER_OUT);
	return 1;
}