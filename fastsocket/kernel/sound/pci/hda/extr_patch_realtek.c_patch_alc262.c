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
struct hda_codec {int /*<<< orphan*/  patch_ops; struct alc_spec* spec; } ;
struct TYPE_2__ {int shared_mic_vref_pin; int beep_nid; int /*<<< orphan*/  no_analog; } ;
struct alc_spec {int /*<<< orphan*/  shutup; TYPE_1__ gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_PROC_COEF ; 
 int /*<<< orphan*/  AC_VERB_SET_COEF_INDEX ; 
 int /*<<< orphan*/  AC_VERB_SET_PROC_COEF ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int /*<<< orphan*/  alc262_fixup_models ; 
 int /*<<< orphan*/  alc262_fixup_tbl ; 
 int /*<<< orphan*/  alc262_fixups ; 
 int alc262_parse_auto_config (struct hda_codec*) ; 
 int alc_alloc_spec (struct hda_codec*,int) ; 
 int /*<<< orphan*/  alc_auto_parse_customize_define (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_eapd_shutup ; 
 int /*<<< orphan*/  alc_fix_pll_init (struct hda_codec*,int,int,int) ; 
 int /*<<< orphan*/  alc_free (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_patch_ops ; 
 scalar_t__ has_cdefine_beep (struct hda_codec*) ; 
 int /*<<< orphan*/  set_beep_amp (struct alc_spec*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_codec_read (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_pick_fixup (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_alc262(struct hda_codec *codec)
{
	struct alc_spec *spec;
	int err;

	err = alc_alloc_spec(codec, 0x0b);
	if (err < 0)
		return err;

	spec = codec->spec;
	spec->gen.shared_mic_vref_pin = 0x18;

#if 0
	/* pshou 07/11/05  set a zero PCM sample to DAC when FIFO is
	 * under-run
	 */
	{
	int tmp;
	snd_hda_codec_write(codec, 0x1a, 0, AC_VERB_SET_COEF_INDEX, 7);
	tmp = snd_hda_codec_read(codec, 0x20, 0, AC_VERB_GET_PROC_COEF, 0);
	snd_hda_codec_write(codec, 0x1a, 0, AC_VERB_SET_COEF_INDEX, 7);
	snd_hda_codec_write(codec, 0x1a, 0, AC_VERB_SET_PROC_COEF, tmp | 0x80);
	}
#endif
	alc_fix_pll_init(codec, 0x20, 0x0a, 10);

	snd_hda_pick_fixup(codec, alc262_fixup_models, alc262_fixup_tbl,
		       alc262_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	alc_auto_parse_customize_define(codec);

	if (has_cdefine_beep(codec))
		spec->gen.beep_nid = 0x01;

	/* automatic parse from the BIOS config */
	err = alc262_parse_auto_config(codec);
	if (err < 0)
		goto error;

	if (!spec->gen.no_analog && spec->gen.beep_nid)
		set_beep_amp(spec, 0x0b, 0x05, HDA_INPUT);

	codec->patch_ops = alc_patch_ops;
	spec->shutup = alc_eapd_shutup;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	return 0;

 error:
	alc_free(codec);
	return err;
}