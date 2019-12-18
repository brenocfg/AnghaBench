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
struct TYPE_4__ {scalar_t__ hook; } ;
struct TYPE_3__ {int num_dacs; int /*<<< orphan*/ * extra_out_nid; int /*<<< orphan*/ * hp_out_nid; } ;
struct auto_pin_cfg {int line_outs; int line_out_type; scalar_t__ speaker_outs; scalar_t__ hp_outs; } ;
struct hda_gen_spec {scalar_t__ multi_ios; int /*<<< orphan*/ * speaker_paths; int /*<<< orphan*/ * hp_paths; TYPE_2__ vmaster_mute; TYPE_1__ multiout; int /*<<< orphan*/  mixer_nid; struct auto_pin_cfg autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
#define  AUTO_PIN_HP_OUT 129 
#define  AUTO_PIN_SPEAKER_OUT 128 
 char const** channel_name ; 
 int /*<<< orphan*/  path_has_mixer (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_BUG () ; 

__attribute__((used)) static const char *get_line_out_pfx(struct hda_codec *codec, int ch,
				    int *index, int ctl_type)
{
	struct hda_gen_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->autocfg;

	*index = 0;
	if (cfg->line_outs == 1 && !spec->multi_ios &&
	    !cfg->hp_outs && !cfg->speaker_outs)
		return spec->vmaster_mute.hook ? "PCM" : "Master";

	/* if there is really a single DAC used in the whole output paths,
	 * use it master (or "PCM" if a vmaster hook is present)
	 */
	if (spec->multiout.num_dacs == 1 && !spec->mixer_nid &&
	    !spec->multiout.hp_out_nid[0] && !spec->multiout.extra_out_nid[0])
		return spec->vmaster_mute.hook ? "PCM" : "Master";

	/* multi-io channels */
	if (ch >= cfg->line_outs)
		return channel_name[ch];

	switch (cfg->line_out_type) {
	case AUTO_PIN_SPEAKER_OUT:
		/* if the primary channel vol/mute is shared with HP volume,
		 * don't name it as Speaker
		 */
		if (!ch && cfg->hp_outs &&
		    !path_has_mixer(codec, spec->hp_paths[0], ctl_type))
			break;
		if (cfg->line_outs == 1)
			return "Speaker";
		if (cfg->line_outs == 2)
			return ch ? "Bass Speaker" : "Speaker";
		break;
	case AUTO_PIN_HP_OUT:
		/* if the primary channel vol/mute is shared with spk volume,
		 * don't name it as Headphone
		 */
		if (!ch && cfg->speaker_outs &&
		    !path_has_mixer(codec, spec->speaker_paths[0], ctl_type))
			break;
		/* for multi-io case, only the primary out */
		if (ch && spec->multi_ios)
			break;
		*index = ch;
		return "Headphone";
	}

	/* for a single channel output, we don't have to name the channel */
	if (cfg->line_outs == 1 && !spec->multi_ios)
		return "PCM";

	if (ch >= ARRAY_SIZE(channel_name)) {
		snd_BUG();
		return "PCM";
	}

	return channel_name[ch];
}