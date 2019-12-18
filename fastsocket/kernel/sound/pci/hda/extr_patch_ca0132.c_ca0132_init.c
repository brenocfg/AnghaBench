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
struct hda_codec {struct ca0132_spec* spec; } ;
struct auto_pin_cfg {int /*<<< orphan*/  dig_in_pin; int /*<<< orphan*/ * dig_out_pins; } ;
struct ca0132_spec {int num_outputs; int num_inputs; int num_init_verbs; int /*<<< orphan*/ * init_verbs; int /*<<< orphan*/  dig_in; int /*<<< orphan*/ * adcs; int /*<<< orphan*/ * input_pins; int /*<<< orphan*/  dig_out; int /*<<< orphan*/ * dacs; int /*<<< orphan*/ * out_pins; int /*<<< orphan*/  base_init_verbs; int /*<<< orphan*/  curr_chip_addx; int /*<<< orphan*/  dsp_state; struct auto_pin_cfg autocfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_DOWNLOAD_INIT ; 
 int /*<<< orphan*/  INVALID_CHIP_ADDRESS ; 
 int /*<<< orphan*/  ca0132_download_dsp (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_init_analog_mic2 (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_init_dmic (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_init_flags (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_init_params (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_init_unsol (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_refresh_widget_caps (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_select_mic (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_select_out (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_setup_defaults (struct hda_codec*) ; 
 int /*<<< orphan*/  init_input (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_output (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_jack_report_sync (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_power_down (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_power_up (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca0132_init(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->autocfg;
	int i;

	spec->dsp_state = DSP_DOWNLOAD_INIT;
	spec->curr_chip_addx = INVALID_CHIP_ADDRESS;

	snd_hda_power_up(codec);

	ca0132_init_params(codec);
	ca0132_init_flags(codec);
	snd_hda_sequence_write(codec, spec->base_init_verbs);
	ca0132_download_dsp(codec);
	ca0132_refresh_widget_caps(codec);
	ca0132_setup_defaults(codec);
	ca0132_init_analog_mic2(codec);
	ca0132_init_dmic(codec);

	for (i = 0; i < spec->num_outputs; i++)
		init_output(codec, spec->out_pins[i], spec->dacs[0]);

	init_output(codec, cfg->dig_out_pins[0], spec->dig_out);

	for (i = 0; i < spec->num_inputs; i++)
		init_input(codec, spec->input_pins[i], spec->adcs[i]);

	init_input(codec, cfg->dig_in_pin, spec->dig_in);

	for (i = 0; i < spec->num_init_verbs; i++)
		snd_hda_sequence_write(codec, spec->init_verbs[i]);

	ca0132_init_unsol(codec);

	ca0132_select_out(codec);
	ca0132_select_mic(codec);

	snd_hda_jack_report_sync(codec);

	snd_hda_power_down(codec);

	return 0;
}