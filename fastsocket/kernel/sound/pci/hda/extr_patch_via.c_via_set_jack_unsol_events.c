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
struct auto_pin_cfg {int line_outs; int num_inputs; scalar_t__* line_out_pins; scalar_t__* speaker_pins; } ;
struct TYPE_2__ {int /*<<< orphan*/  line_automute_hook; int /*<<< orphan*/  hp_automute_hook; struct auto_pin_cfg autocfg; } ;
struct via_spec {TYPE_1__ gen; } ;
struct hda_codec {struct via_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIA_JACK_EVENT ; 
 scalar_t__ is_jack_detectable (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable_callback (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_jack_tbl_get (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  via_hp_automute ; 
 int /*<<< orphan*/  via_jack_powerstate_event ; 
 int /*<<< orphan*/  via_line_automute ; 

__attribute__((used)) static void via_set_jack_unsol_events(struct hda_codec *codec)
{
	struct via_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->gen.autocfg;
	hda_nid_t pin;
	int i;

	spec->gen.hp_automute_hook = via_hp_automute;
	if (cfg->speaker_pins[0])
		spec->gen.line_automute_hook = via_line_automute;

	for (i = 0; i < cfg->line_outs; i++) {
		pin = cfg->line_out_pins[i];
		if (pin && !snd_hda_jack_tbl_get(codec, pin) &&
		    is_jack_detectable(codec, pin))
			snd_hda_jack_detect_enable_callback(codec, pin,
							    VIA_JACK_EVENT,
							    via_jack_powerstate_event);
	}

	for (i = 0; i < cfg->num_inputs; i++) {
		pin = cfg->line_out_pins[i];
		if (pin && !snd_hda_jack_tbl_get(codec, pin) &&
		    is_jack_detectable(codec, pin))
			snd_hda_jack_detect_enable_callback(codec, pin,
							    VIA_JACK_EVENT,
							    via_jack_powerstate_event);
	}
}