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
struct nid_path {int dummy; } ;
struct auto_pin_cfg {scalar_t__ line_out_type; scalar_t__ speaker_outs; scalar_t__ hp_outs; scalar_t__ line_outs; scalar_t__* speaker_pins; scalar_t__* hp_pins; scalar_t__* line_out_pins; } ;
struct hda_gen_spec {scalar_t__ indep_hp; scalar_t__ prefer_hp_amp; int /*<<< orphan*/  vmaster_tlv; int /*<<< orphan*/  vmaster_nid; int /*<<< orphan*/ * out_paths; struct auto_pin_cfg autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_HP_OUT ; 
 scalar_t__ AUTO_PIN_SPEAKER_OUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int INT_MAX ; 
 unsigned int PIN_HP ; 
 unsigned int PIN_OUT ; 
 int /*<<< orphan*/  debug_badness (char*,...) ; 
 int /*<<< orphan*/  debug_show_configs (struct hda_codec*,struct auto_pin_cfg*) ; 
 int fill_and_eval_dacs (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  indep_hp_possible (struct hda_codec*) ; 
 int /*<<< orphan*/  kfree (struct auto_pin_cfg*) ; 
 struct auto_pin_cfg* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  look_for_out_vol_nid (struct hda_codec*,struct nid_path*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_pin_targets (struct hda_codec*,scalar_t__,scalar_t__*,unsigned int) ; 
 struct nid_path* snd_hda_get_path_from_idx (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_set_vmaster_tlv (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_output_paths(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->autocfg;
	struct auto_pin_cfg *best_cfg;
	unsigned int val;
	int best_badness = INT_MAX;
	int badness;
	bool fill_hardwired = true, fill_mio_first = true;
	bool best_wired = true, best_mio = true;
	bool hp_spk_swapped = false;

	best_cfg = kmalloc(sizeof(*best_cfg), GFP_KERNEL);
	if (!best_cfg)
		return -ENOMEM;
	*best_cfg = *cfg;

	for (;;) {
		badness = fill_and_eval_dacs(codec, fill_hardwired,
					     fill_mio_first);
		if (badness < 0) {
			kfree(best_cfg);
			return badness;
		}
		debug_badness("==> lo_type=%d, wired=%d, mio=%d, badness=0x%x\n",
			      cfg->line_out_type, fill_hardwired, fill_mio_first,
			      badness);
		debug_show_configs(codec, cfg);
		if (badness < best_badness) {
			best_badness = badness;
			*best_cfg = *cfg;
			best_wired = fill_hardwired;
			best_mio = fill_mio_first;
		}
		if (!badness)
			break;
		fill_mio_first = !fill_mio_first;
		if (!fill_mio_first)
			continue;
		fill_hardwired = !fill_hardwired;
		if (!fill_hardwired)
			continue;
		if (hp_spk_swapped)
			break;
		hp_spk_swapped = true;
		if (cfg->speaker_outs > 0 &&
		    cfg->line_out_type == AUTO_PIN_HP_OUT) {
			cfg->hp_outs = cfg->line_outs;
			memcpy(cfg->hp_pins, cfg->line_out_pins,
			       sizeof(cfg->hp_pins));
			cfg->line_outs = cfg->speaker_outs;
			memcpy(cfg->line_out_pins, cfg->speaker_pins,
			       sizeof(cfg->speaker_pins));
			cfg->speaker_outs = 0;
			memset(cfg->speaker_pins, 0, sizeof(cfg->speaker_pins));
			cfg->line_out_type = AUTO_PIN_SPEAKER_OUT;
			fill_hardwired = true;
			continue;
		}
		if (cfg->hp_outs > 0 &&
		    cfg->line_out_type == AUTO_PIN_SPEAKER_OUT) {
			cfg->speaker_outs = cfg->line_outs;
			memcpy(cfg->speaker_pins, cfg->line_out_pins,
			       sizeof(cfg->speaker_pins));
			cfg->line_outs = cfg->hp_outs;
			memcpy(cfg->line_out_pins, cfg->hp_pins,
			       sizeof(cfg->hp_pins));
			cfg->hp_outs = 0;
			memset(cfg->hp_pins, 0, sizeof(cfg->hp_pins));
			cfg->line_out_type = AUTO_PIN_HP_OUT;
			fill_hardwired = true;
			continue;
		}
		break;
	}

	if (badness) {
		debug_badness("==> restoring best_cfg\n");
		*cfg = *best_cfg;
		fill_and_eval_dacs(codec, best_wired, best_mio);
	}
	debug_badness("==> Best config: lo_type=%d, wired=%d, mio=%d\n",
		      cfg->line_out_type, best_wired, best_mio);
	debug_show_configs(codec, cfg);

	if (cfg->line_out_pins[0]) {
		struct nid_path *path;
		path = snd_hda_get_path_from_idx(codec, spec->out_paths[0]);
		if (path)
			spec->vmaster_nid = look_for_out_vol_nid(codec, path);
		if (spec->vmaster_nid)
			snd_hda_set_vmaster_tlv(codec, spec->vmaster_nid,
						HDA_OUTPUT, spec->vmaster_tlv);
	}

	/* set initial pinctl targets */
	if (spec->prefer_hp_amp || cfg->line_out_type == AUTO_PIN_HP_OUT)
		val = PIN_HP;
	else
		val = PIN_OUT;
	set_pin_targets(codec, cfg->line_outs, cfg->line_out_pins, val);
	if (cfg->line_out_type != AUTO_PIN_HP_OUT)
		set_pin_targets(codec, cfg->hp_outs, cfg->hp_pins, PIN_HP);
	if (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT) {
		val = spec->prefer_hp_amp ? PIN_HP : PIN_OUT;
		set_pin_targets(codec, cfg->speaker_outs,
				cfg->speaker_pins, val);
	}

	/* clear indep_hp flag if not available */
	if (spec->indep_hp && !indep_hp_possible(codec))
		spec->indep_hp = 0;

	kfree(best_cfg);
	return 0;
}