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
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct sigmatel_spec {int mic_mute_led_on; int /*<<< orphan*/  gpio_data; int /*<<< orphan*/  gpio_dir; int /*<<< orphan*/  gpio_mask; int /*<<< orphan*/  mic_mute_led_gpio; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  stac_gpio_set (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stac_capture_led_hook(struct hda_codec *codec,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct sigmatel_spec *spec = codec->spec;
	bool mute;

	if (!ucontrol)
		return;

	mute = !(ucontrol->value.integer.value[0] ||
		 ucontrol->value.integer.value[1]);
	if (spec->mic_mute_led_on != mute) {
		spec->mic_mute_led_on = mute;
		if (mute)
			spec->gpio_data |= spec->mic_mute_led_gpio;
		else
			spec->gpio_data &= ~spec->mic_mute_led_gpio;
		stac_gpio_set(codec, spec->gpio_mask,
			      spec->gpio_dir, spec->gpio_data);
	}
}