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
struct hda_codec {struct ad198x_spec* spec; } ;
struct TYPE_2__ {int mixer_nid; int beep_nid; } ;
struct ad198x_spec {TYPE_1__ gen; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int /*<<< orphan*/  ad1981_fixup_tbl ; 
 int /*<<< orphan*/  ad1981_fixups ; 
 int ad1983_add_spdif_mux_ctl (struct hda_codec*) ; 
 int ad198x_parse_auto_config (struct hda_codec*) ; 
 int alloc_ad_spec (struct hda_codec*) ; 
 int /*<<< orphan*/  set_beep_amp (struct ad198x_spec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_gen_free (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_pick_fixup (struct hda_codec*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad1981_parse_auto_config(struct hda_codec *codec)
{
	struct ad198x_spec *spec;
	int err;

	err = alloc_ad_spec(codec);
	if (err < 0)
		return -ENOMEM;
	spec = codec->spec;

	spec->gen.mixer_nid = 0x0e;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x0d, 0, HDA_OUTPUT);

	snd_hda_pick_fixup(codec, NULL, ad1981_fixup_tbl, ad1981_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = ad198x_parse_auto_config(codec);
	if (err < 0)
		goto error;
	err = ad1983_add_spdif_mux_ctl(codec);
	if (err < 0)
		goto error;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	return 0;

 error:
	snd_hda_gen_free(codec);
	return err;
}