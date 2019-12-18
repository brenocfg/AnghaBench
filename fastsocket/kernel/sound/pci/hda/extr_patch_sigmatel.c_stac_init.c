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
struct TYPE_2__ {int num_all_adcs; int /*<<< orphan*/ * all_adcs; } ;
struct sigmatel_spec {unsigned int gpio_data; unsigned int eapd_mask; int active_adcs; TYPE_1__ gen; scalar_t__ powerdown_adcs; int /*<<< orphan*/  power_map_bits; scalar_t__ num_pwrs; int /*<<< orphan*/  gpio_dir; int /*<<< orphan*/  gpio_mask; int /*<<< orphan*/  eapd_switch; } ;
struct hda_codec {int /*<<< orphan*/  afg; struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PWRST_D3 ; 
 int /*<<< orphan*/  AC_VERB_IDT_SET_POWER_MAP ; 
 int /*<<< orphan*/  AC_VERB_SET_POWER_STATE ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_gen_init (struct hda_codec*) ; 
 int /*<<< orphan*/  stac_gpio_set (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stac_store_hints (struct hda_codec*) ; 

__attribute__((used)) static int stac_init(struct hda_codec *codec)
{
	struct sigmatel_spec *spec = codec->spec;
	unsigned int gpio;
	int i;

	/* override some hints */
	stac_store_hints(codec);

	/* set up GPIO */
	gpio = spec->gpio_data;
	/* turn on EAPD statically when spec->eapd_switch isn't set.
	 * otherwise, unsol event will turn it on/off dynamically
	 */
	if (!spec->eapd_switch)
		gpio |= spec->eapd_mask;
	stac_gpio_set(codec, spec->gpio_mask, spec->gpio_dir, gpio);

	snd_hda_gen_init(codec);

	/* sync the power-map */
	if (spec->num_pwrs)
		snd_hda_codec_write(codec, codec->afg, 0,
				    AC_VERB_IDT_SET_POWER_MAP,
				    spec->power_map_bits);

	/* power down inactive ADCs */
	if (spec->powerdown_adcs) {
		for (i = 0; i < spec->gen.num_all_adcs; i++) {
			if (spec->active_adcs & (1 << i))
				continue;
			snd_hda_codec_write(codec, spec->gen.all_adcs[i], 0,
					    AC_VERB_SET_POWER_STATE,
					    AC_PWRST_D3);
		}
	}

	return 0;
}