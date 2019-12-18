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
struct hda_gen_spec {int /*<<< orphan*/  loopback_merge_path; int /*<<< orphan*/ * loopback_paths; scalar_t__ mixer_nid; struct auto_pin_cfg autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_2__ {int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 scalar_t__ is_input_pin (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_pin_ctl (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resume_path_from_idx (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_analog_input(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->autocfg;
	int i;

	for (i = 0; i < cfg->num_inputs; i++) {
		hda_nid_t nid = cfg->inputs[i].pin;
		if (is_input_pin(codec, nid))
			restore_pin_ctl(codec, nid);

		/* init loopback inputs */
		if (spec->mixer_nid) {
			resume_path_from_idx(codec, spec->loopback_paths[i]);
			resume_path_from_idx(codec, spec->loopback_merge_path);
		}
	}
}