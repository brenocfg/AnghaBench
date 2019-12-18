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
struct hda_verb {int member_0; int member_2; int /*<<< orphan*/  member_1; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  hook; } ;
struct TYPE_4__ {int /*<<< orphan*/  cap_sync_hook; TYPE_1__ vmaster_mute; } ;
struct alc_spec {scalar_t__ gpio_led; TYPE_2__ gen; } ;

/* Variables and functions */
#define  AC_VERB_SET_GPIO_DIRECTION 129 
#define  AC_VERB_SET_GPIO_MASK 128 
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  alc269_fixup_hp_gpio_mic_mute_hook ; 
 int /*<<< orphan*/  alc269_fixup_hp_gpio_mute_hook ; 
 int /*<<< orphan*/  snd_hda_add_verbs (struct hda_codec*,struct hda_verb const*) ; 

__attribute__((used)) static void alc269_fixup_hp_gpio_led(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;
	static const struct hda_verb gpio_init[] = {
		{ 0x01, AC_VERB_SET_GPIO_MASK, 0x18 },
		{ 0x01, AC_VERB_SET_GPIO_DIRECTION, 0x18 },
		{}
	};

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->gen.vmaster_mute.hook = alc269_fixup_hp_gpio_mute_hook;
		spec->gen.cap_sync_hook = alc269_fixup_hp_gpio_mic_mute_hook;
		spec->gpio_led = 0;
		snd_hda_add_verbs(codec, gpio_init);
	}
}