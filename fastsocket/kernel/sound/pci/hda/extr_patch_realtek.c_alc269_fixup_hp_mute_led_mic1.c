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
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  hook; } ;
struct TYPE_4__ {int vmaster_mute_enum; TYPE_1__ vmaster_mute; } ;
struct alc_spec {int mute_led_nid; TYPE_2__ gen; scalar_t__ mute_led_polarity; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  alc269_fixup_mic_mute_hook ; 

__attribute__((used)) static void alc269_fixup_hp_mute_led_mic1(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->mute_led_polarity = 0;
		spec->mute_led_nid = 0x18;
		spec->gen.vmaster_mute.hook = alc269_fixup_mic_mute_hook;
		spec->gen.vmaster_mute_enum = 1;
	}
}