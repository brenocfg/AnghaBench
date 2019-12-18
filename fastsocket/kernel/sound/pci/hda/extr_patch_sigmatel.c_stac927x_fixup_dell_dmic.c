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
struct sigmatel_spec {int eapd_mask; int gpio_mask; int gpio_dir; int gpio_data; int volknob_init; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {int subsystem_id; struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  dell_3st_core_init ; 
 int /*<<< orphan*/  snd_hda_add_verbs (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stac927x_fixup_dell_dmic(struct hda_codec *codec,
				     const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	if (codec->subsystem_id != 0x1028022f) {
		/* GPIO2 High = Enable EAPD */
		spec->eapd_mask = spec->gpio_mask = 0x04;
		spec->gpio_dir = spec->gpio_data = 0x04;
	}

	snd_hda_add_verbs(codec, dell_3st_core_init);
	spec->volknob_init = 1;
}