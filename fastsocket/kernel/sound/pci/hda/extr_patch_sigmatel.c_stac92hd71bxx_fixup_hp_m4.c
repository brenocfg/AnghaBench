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
struct sigmatel_spec {int gpio_mask; } ;
struct hda_jack_tbl {int private_data; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {int /*<<< orphan*/  afg; struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_GPIO_UNSOLICITED_RSP_MASK ; 
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  STAC_VREF_EVENT ; 
 int /*<<< orphan*/  snd_hda_codec_set_pincfg (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  snd_hda_codec_write_cache (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable_callback (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_get (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stac_vref_event ; 

__attribute__((used)) static void stac92hd71bxx_fixup_hp_m4(struct hda_codec *codec,
				      const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;
	struct hda_jack_tbl *jack;

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	/* Enable VREF power saving on GPIO1 detect */
	snd_hda_codec_write_cache(codec, codec->afg, 0,
				  AC_VERB_SET_GPIO_UNSOLICITED_RSP_MASK, 0x02);
	snd_hda_jack_detect_enable_callback(codec, codec->afg,
					    STAC_VREF_EVENT,
					    stac_vref_event);
	jack = snd_hda_jack_tbl_get(codec, codec->afg);
	if (jack)
		jack->private_data = 0x02;

	spec->gpio_mask |= 0x02;

	/* enable internal microphone */
	snd_hda_codec_set_pincfg(codec, 0x0e, 0x01813040);
}