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
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {unsigned int gpio_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DATA ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void alc269_fixup_hp_gpio_mute_hook(void *private_data, int enabled)
{
	struct hda_codec *codec = private_data;
	struct alc_spec *spec = codec->spec;
	unsigned int oldval = spec->gpio_led;

	if (enabled)
		spec->gpio_led &= ~0x08;
	else
		spec->gpio_led |= 0x08;
	if (spec->gpio_led != oldval)
		snd_hda_codec_write(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_led);
}