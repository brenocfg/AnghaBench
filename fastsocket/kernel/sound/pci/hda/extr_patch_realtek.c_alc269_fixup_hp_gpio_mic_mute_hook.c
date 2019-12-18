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
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {unsigned int gpio_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DATA ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void alc269_fixup_hp_gpio_mic_mute_hook(struct hda_codec *codec,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct alc_spec *spec = codec->spec;
	unsigned int oldval = spec->gpio_led;

	if (!ucontrol)
		return;

	if (ucontrol->value.integer.value[0] ||
	    ucontrol->value.integer.value[1])
		spec->gpio_led &= ~0x10;
	else
		spec->gpio_led |= 0x10;
	if (spec->gpio_led != oldval)
		snd_hda_codec_write(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_led);
}