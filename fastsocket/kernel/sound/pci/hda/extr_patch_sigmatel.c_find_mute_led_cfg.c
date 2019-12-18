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
struct sigmatel_spec {unsigned int gpio_led; unsigned int gpio_led_polarity; int vref_mute_led_nid; } ;
struct hda_codec {int /*<<< orphan*/  subsystem_id; int /*<<< orphan*/  afg; struct sigmatel_spec* spec; } ;
struct dmi_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int AC_GPIO_IO_COUNT ; 
 int /*<<< orphan*/  AC_PAR_GPIO_CAP ; 
 int /*<<< orphan*/  DMI_DEV_TYPE_OEM_STRING ; 
 struct dmi_device* dmi_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmi_device const*) ; 
 scalar_t__ get_int_hint (struct hda_codec*,char*,unsigned int*) ; 
 int /*<<< orphan*/  hp_blike_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hp_led_gpio (struct hda_codec*) ; 
 unsigned int snd_hda_param_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*,...) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int find_mute_led_cfg(struct hda_codec *codec, int default_polarity)
{
	struct sigmatel_spec *spec = codec->spec;
	const struct dmi_device *dev = NULL;

	if (get_int_hint(codec, "gpio_led", &spec->gpio_led)) {
		get_int_hint(codec, "gpio_led_polarity",
			     &spec->gpio_led_polarity);
		return 1;
	}

	while ((dev = dmi_find_device(DMI_DEV_TYPE_OEM_STRING, NULL, dev))) {
		if (sscanf(dev->name, "HP_Mute_LED_%d_%x",
			   &spec->gpio_led_polarity,
			   &spec->gpio_led) == 2) {
			unsigned int max_gpio;
			max_gpio = snd_hda_param_read(codec, codec->afg,
						      AC_PAR_GPIO_CAP);
			max_gpio &= AC_GPIO_IO_COUNT;
			if (spec->gpio_led < max_gpio)
				spec->gpio_led = 1 << spec->gpio_led;
			else
				spec->vref_mute_led_nid = spec->gpio_led;
			return 1;
		}
		if (sscanf(dev->name, "HP_Mute_LED_%d",
			   &spec->gpio_led_polarity) == 1) {
			set_hp_led_gpio(codec);
			return 1;
		}
		/* BIOS bug: unfilled OEM string */
		if (strstr(dev->name, "HP_Mute_LED_P_G")) {
			set_hp_led_gpio(codec);
			if (default_polarity >= 0)
				spec->gpio_led_polarity = default_polarity;
			else
				spec->gpio_led_polarity = 1;
			return 1;
		}
	}

	/*
	 * Fallback case - if we don't find the DMI strings,
	 * we statically set the GPIO - if not a B-series system
	 * and default polarity is provided
	 */
	if (!hp_blike_system(codec->subsystem_id) &&
	    (default_polarity == 0 || default_polarity == 1)) {
		set_hp_led_gpio(codec);
		spec->gpio_led_polarity = default_polarity;
		return 1;
	}
	return 0;
}