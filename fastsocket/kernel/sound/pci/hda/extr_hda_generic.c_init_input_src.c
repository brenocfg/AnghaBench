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
struct nid_path {int active; } ;
struct hda_input_mux {int num_items; } ;
struct hda_gen_spec {int num_adc_nids; int* cur_mux; int /*<<< orphan*/  (* cap_sync_hook ) (struct hda_codec*,int /*<<< orphan*/ *) ;scalar_t__ hp_mic; scalar_t__ dyn_adc_switch; struct hda_input_mux input_mux; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 struct nid_path* get_input_path (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  snd_hda_activate_path (struct hda_codec*,struct nid_path*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_hp_mic (struct hda_codec*,int,int) ; 

__attribute__((used)) static void init_input_src(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	struct hda_input_mux *imux = &spec->input_mux;
	struct nid_path *path;
	int i, c, nums;

	if (spec->dyn_adc_switch)
		nums = 1;
	else
		nums = spec->num_adc_nids;

	for (c = 0; c < nums; c++) {
		for (i = 0; i < imux->num_items; i++) {
			path = get_input_path(codec, c, i);
			if (path) {
				bool active = path->active;
				if (i == spec->cur_mux[c])
					active = true;
				snd_hda_activate_path(codec, path, active, false);
			}
		}
		if (spec->hp_mic)
			update_hp_mic(codec, c, true);
	}

	if (spec->cap_sync_hook)
		spec->cap_sync_hook(codec, NULL);
}