#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hda_codec {int vendor_id; int /*<<< orphan*/  patch_ops; TYPE_2__* bus; struct alc_spec* spec; } ;
struct TYPE_8__ {int beep_nid; int /*<<< orphan*/  no_analog; } ;
struct TYPE_7__ {int platform_type; } ;
struct alc_spec {int /*<<< orphan*/  shutup; TYPE_4__ gen; TYPE_3__ cdefine; int /*<<< orphan*/  (* init_hook ) (struct hda_codec*) ;int /*<<< orphan*/  parse_flags; } ;
struct TYPE_6__ {TYPE_1__* pci; } ;
struct TYPE_5__ {int subsystem_vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int /*<<< orphan*/  HDA_PINCFG_NO_HP_FIXUP ; 
 int /*<<< orphan*/  alc662_fill_coef (struct hda_codec*) ; 
 int /*<<< orphan*/  alc662_fixup_models ; 
 int /*<<< orphan*/  alc662_fixup_tbl ; 
 int /*<<< orphan*/  alc662_fixups ; 
 int alc662_parse_auto_config (struct hda_codec*) ; 
 int alc_alloc_spec (struct hda_codec*,int) ; 
 int /*<<< orphan*/  alc_auto_parse_customize_define (struct hda_codec*) ; 
 int alc_codec_rename (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  alc_eapd_shutup ; 
 int /*<<< orphan*/  alc_fix_pll_init (struct hda_codec*,int,int,int) ; 
 int /*<<< orphan*/  alc_free (struct hda_codec*) ; 
 int alc_get_coef0 (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_patch_ops ; 
 scalar_t__ has_cdefine_beep (struct hda_codec*) ; 
 int /*<<< orphan*/  set_beep_amp (struct alc_spec*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_pick_fixup (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_alc662(struct hda_codec *codec)
{
	struct alc_spec *spec;
	int err;

	err = alc_alloc_spec(codec, 0x0b);
	if (err < 0)
		return err;

	spec = codec->spec;

	/* handle multiple HPs as is */
	spec->parse_flags = HDA_PINCFG_NO_HP_FIXUP;

	alc_fix_pll_init(codec, 0x20, 0x04, 15);

	spec->init_hook = alc662_fill_coef;
	alc662_fill_coef(codec);

	snd_hda_pick_fixup(codec, alc662_fixup_models,
		       alc662_fixup_tbl, alc662_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	alc_auto_parse_customize_define(codec);

	if (has_cdefine_beep(codec))
		spec->gen.beep_nid = 0x01;

	if ((alc_get_coef0(codec) & (1 << 14)) &&
	    codec->bus->pci->subsystem_vendor == 0x1025 &&
	    spec->cdefine.platform_type == 1) {
		err = alc_codec_rename(codec, "ALC272X");
		if (err < 0)
			goto error;
	}

	/* automatic parse from the BIOS config */
	err = alc662_parse_auto_config(codec);
	if (err < 0)
		goto error;

	if (!spec->gen.no_analog && spec->gen.beep_nid) {
		switch (codec->vendor_id) {
		case 0x10ec0662:
			set_beep_amp(spec, 0x0b, 0x05, HDA_INPUT);
			break;
		case 0x10ec0272:
		case 0x10ec0663:
		case 0x10ec0665:
			set_beep_amp(spec, 0x0b, 0x04, HDA_INPUT);
			break;
		case 0x10ec0273:
			set_beep_amp(spec, 0x0b, 0x03, HDA_INPUT);
			break;
		}
	}

	codec->patch_ops = alc_patch_ops;
	spec->shutup = alc_eapd_shutup;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	return 0;

 error:
	alc_free(codec);
	return err;
}