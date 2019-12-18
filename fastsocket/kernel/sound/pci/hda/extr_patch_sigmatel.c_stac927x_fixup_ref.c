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
struct sigmatel_spec {scalar_t__ gpio_data; scalar_t__ gpio_dir; scalar_t__ gpio_mask; scalar_t__ eapd_mask; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  ref927x_pin_configs ; 
 int /*<<< orphan*/  snd_hda_apply_pincfgs (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stac927x_fixup_ref(struct hda_codec *codec,
			       const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		snd_hda_apply_pincfgs(codec, ref927x_pin_configs);
		spec->eapd_mask = spec->gpio_mask = 0;
		spec->gpio_dir = spec->gpio_data = 0;
	}
}