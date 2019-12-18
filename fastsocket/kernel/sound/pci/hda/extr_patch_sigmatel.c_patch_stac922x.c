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
struct TYPE_2__ {int own_eapd_ctl; } ;
struct sigmatel_spec {int linear_tone_beep; TYPE_1__ gen; } ;
struct hda_codec {int /*<<< orphan*/  patch_ops; struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int AC_AMPCAP_MUTE_SHIFT ; 
 int AC_AMPCAP_NUM_STEPS_SHIFT ; 
 int AC_AMPCAP_OFFSET_SHIFT ; 
 int AC_AMPCAP_STEP_SIZE_SHIFT ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int alloc_stac_spec (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_add_verbs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_override_amp_caps (struct hda_codec*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_pick_fixup (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stac922x_core_init ; 
 int /*<<< orphan*/  stac922x_fixup_tbl ; 
 int /*<<< orphan*/  stac922x_fixups ; 
 int /*<<< orphan*/  stac922x_models ; 
 int /*<<< orphan*/  stac_free (struct hda_codec*) ; 
 int stac_parse_auto_config (struct hda_codec*) ; 
 int /*<<< orphan*/  stac_patch_ops ; 

__attribute__((used)) static int patch_stac922x(struct hda_codec *codec)
{
	struct sigmatel_spec *spec;
	int err;

	err = alloc_stac_spec(codec);
	if (err < 0)
		return err;

	spec = codec->spec;
	spec->linear_tone_beep = 1;
	spec->gen.own_eapd_ctl = 1;

	codec->patch_ops = stac_patch_ops;

	snd_hda_add_verbs(codec, stac922x_core_init);

	/* Fix Mux capture level; max to 2 */
	snd_hda_override_amp_caps(codec, 0x12, HDA_OUTPUT,
				  (0 << AC_AMPCAP_OFFSET_SHIFT) |
				  (2 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x27 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (0 << AC_AMPCAP_MUTE_SHIFT));

	snd_hda_pick_fixup(codec, stac922x_models, stac922x_fixup_tbl,
			   stac922x_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = stac_parse_auto_config(codec);
	if (err < 0) {
		stac_free(codec);
		return err;
	}

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	return 0;
}