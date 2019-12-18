#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct auto_pin_cfg {int num_inputs; TYPE_1__* inputs; } ;
struct hda_gen_spec {scalar_t__ mixer_nid; scalar_t__ hp_mic_pin; char** input_labels; scalar_t__ add_stereo_mix_input; scalar_t__ add_jack_modes; int /*<<< orphan*/ * input_label_idxs; struct auto_pin_cfg autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;
struct TYPE_2__ {scalar_t__ pin; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_MIC ; 
 int CFG_IDX_MIX ; 
 unsigned int PIN_IN ; 
 int create_in_jack_mode (struct hda_codec*,scalar_t__) ; 
 int fill_adc_nids (struct hda_codec*) ; 
 int fill_input_pin_labels (struct hda_codec*) ; 
 int /*<<< orphan*/  is_input_pin (struct hda_codec*,scalar_t__) ; 
 scalar_t__ is_reachable_path (struct hda_codec*,scalar_t__,scalar_t__) ; 
 int new_analog_input (struct hda_codec*,int,scalar_t__,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int parse_capture_source (struct hda_codec*,scalar_t__,int,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  set_pin_target (struct hda_codec*,scalar_t__,unsigned int,int) ; 
 unsigned int snd_hda_get_default_vref (struct hda_codec*,scalar_t__) ; 

__attribute__((used)) static int create_input_ctls(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	const struct auto_pin_cfg *cfg = &spec->autocfg;
	hda_nid_t mixer = spec->mixer_nid;
	int num_adcs;
	int i, err;
	unsigned int val;

	num_adcs = fill_adc_nids(codec);
	if (num_adcs < 0)
		return 0;

	err = fill_input_pin_labels(codec);
	if (err < 0)
		return err;

	for (i = 0; i < cfg->num_inputs; i++) {
		hda_nid_t pin;

		pin = cfg->inputs[i].pin;
		if (!is_input_pin(codec, pin))
			continue;

		val = PIN_IN;
		if (cfg->inputs[i].type == AUTO_PIN_MIC)
			val |= snd_hda_get_default_vref(codec, pin);
		if (pin != spec->hp_mic_pin)
			set_pin_target(codec, pin, val, false);

		if (mixer) {
			if (is_reachable_path(codec, pin, mixer)) {
				err = new_analog_input(codec, i, pin,
						       spec->input_labels[i],
						       spec->input_label_idxs[i],
						       mixer);
				if (err < 0)
					return err;
			}
		}

		err = parse_capture_source(codec, pin, i, num_adcs,
					   spec->input_labels[i], -mixer);
		if (err < 0)
			return err;

		if (spec->add_jack_modes) {
			err = create_in_jack_mode(codec, pin);
			if (err < 0)
				return err;
		}
	}

	if (mixer && spec->add_stereo_mix_input) {
		err = parse_capture_source(codec, mixer, CFG_IDX_MIX, num_adcs,
					   "Stereo Mix", 0);
		if (err < 0)
			return err;
	}

	return 0;
}