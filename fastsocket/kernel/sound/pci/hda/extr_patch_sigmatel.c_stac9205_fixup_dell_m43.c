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
struct sigmatel_spec {int gpio_dir; int eapd_mask; int gpio_mask; int gpio_mute; int gpio_data; } ;
struct hda_jack_tbl {int private_data; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {int /*<<< orphan*/  afg; struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_GPIO_UNSOLICITED_RSP_MASK ; 
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  STAC_VREF_EVENT ; 
 int /*<<< orphan*/  dell_9205_m43_pin_configs ; 
 int /*<<< orphan*/  snd_hda_apply_pincfgs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write_cache (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable_callback (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_get (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stac_vref_event ; 

__attribute__((used)) static void stac9205_fixup_dell_m43(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;
	struct hda_jack_tbl *jack;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		snd_hda_apply_pincfgs(codec, dell_9205_m43_pin_configs);

		/* Enable unsol response for GPIO4/Dock HP connection */
		snd_hda_codec_write_cache(codec, codec->afg, 0,
			AC_VERB_SET_GPIO_UNSOLICITED_RSP_MASK, 0x10);
		snd_hda_jack_detect_enable_callback(codec, codec->afg,
						    STAC_VREF_EVENT,
						    stac_vref_event);
		jack = snd_hda_jack_tbl_get(codec, codec->afg);
		if (jack)
			jack->private_data = 0x01;

		spec->gpio_dir = 0x0b;
		spec->eapd_mask = 0x01;
		spec->gpio_mask = 0x1b;
		spec->gpio_mute = 0x10;
		/* GPIO0 High = EAPD, GPIO1 Low = Headphone Mute,
		 * GPIO3 Low = DRM
		 */
		spec->gpio_data = 0x01;
	}
}