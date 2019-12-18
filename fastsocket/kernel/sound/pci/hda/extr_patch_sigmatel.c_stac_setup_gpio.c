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
struct TYPE_4__ {int /*<<< orphan*/  cap_sync_hook; } ;
struct sigmatel_spec {int gpio_led; int gpio_mask; int gpio_dir; int gpio_data; int mic_mute_led_gpio; int mic_mute_led_on; TYPE_2__ gen; int /*<<< orphan*/  vref_mute_led_nid; } ;
struct TYPE_3__ {int /*<<< orphan*/  set_power_state; } ;
struct hda_codec {TYPE_1__ patch_ops; struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  stac_capture_led_hook ; 
 int /*<<< orphan*/  stac_set_power_state ; 

__attribute__((used)) static void stac_setup_gpio(struct hda_codec *codec)
{
	struct sigmatel_spec *spec = codec->spec;

	if (spec->gpio_led) {
		if (!spec->vref_mute_led_nid) {
			spec->gpio_mask |= spec->gpio_led;
			spec->gpio_dir |= spec->gpio_led;
			spec->gpio_data |= spec->gpio_led;
		} else {
			codec->patch_ops.set_power_state =
					stac_set_power_state;
		}
	}

	if (spec->mic_mute_led_gpio) {
		spec->gpio_mask |= spec->mic_mute_led_gpio;
		spec->gpio_dir |= spec->mic_mute_led_gpio;
		spec->mic_mute_led_on = true;
		spec->gpio_data |= spec->mic_mute_led_gpio;

		spec->gen.cap_sync_hook = stac_capture_led_hook;
	}
}