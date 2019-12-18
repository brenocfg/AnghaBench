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
struct hda_codec {struct alc_spec* spec; } ;
struct auto_pin_cfg {int num_inputs; TYPE_1__* inputs; } ;
struct TYPE_4__ {int /*<<< orphan*/  hp_automute_hook; int /*<<< orphan*/  automute_hook; int /*<<< orphan*/  cap_sync_hook; struct auto_pin_cfg autocfg; } ;
struct alc_spec {TYPE_2__ gen; scalar_t__ headphone_mic_pin; scalar_t__ headset_mic_pin; } ;
struct TYPE_3__ {scalar_t__ pin; scalar_t__ is_headphone_mic; scalar_t__ is_headset_mic; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_update_headset_jack_cb ; 
 int /*<<< orphan*/  alc_update_headset_mode ; 
 int /*<<< orphan*/  alc_update_headset_mode_hook ; 

__attribute__((used)) static void alc_probe_headset_mode(struct hda_codec *codec)
{
	int i;
	struct alc_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->gen.autocfg;

	/* Find mic pins */
	for (i = 0; i < cfg->num_inputs; i++) {
		if (cfg->inputs[i].is_headset_mic && !spec->headset_mic_pin)
			spec->headset_mic_pin = cfg->inputs[i].pin;
		if (cfg->inputs[i].is_headphone_mic && !spec->headphone_mic_pin)
			spec->headphone_mic_pin = cfg->inputs[i].pin;
	}

	spec->gen.cap_sync_hook = alc_update_headset_mode_hook;
	spec->gen.automute_hook = alc_update_headset_mode;
	spec->gen.hp_automute_hook = alc_update_headset_jack_cb;
}