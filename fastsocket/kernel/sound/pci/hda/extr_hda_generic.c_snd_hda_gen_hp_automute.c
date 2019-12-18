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
struct hda_jack_tbl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * hp_pins; } ;
struct hda_gen_spec {int /*<<< orphan*/  automute_lo; int /*<<< orphan*/  automute_speaker; int /*<<< orphan*/  detect_hp; int /*<<< orphan*/  hp_jack_present; scalar_t__ indep_hp_enabled; TYPE_1__ autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_update_outputs (struct hda_codec*) ; 
 int /*<<< orphan*/  detect_jacks (struct hda_codec*,int,int /*<<< orphan*/ *) ; 

void snd_hda_gen_hp_automute(struct hda_codec *codec, struct hda_jack_tbl *jack)
{
	struct hda_gen_spec *spec = codec->spec;
	hda_nid_t *pins = spec->autocfg.hp_pins;
	int num_pins = ARRAY_SIZE(spec->autocfg.hp_pins);

	/* No detection for the first HP jack during indep-HP mode */
	if (spec->indep_hp_enabled) {
		pins++;
		num_pins--;
	}

	spec->hp_jack_present = detect_jacks(codec, num_pins, pins);
	if (!spec->detect_hp || (!spec->automute_speaker && !spec->automute_lo))
		return;
	call_update_outputs(codec);
}