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
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {int num_adc_nids; scalar_t__* imux_pins; size_t* cur_mux; scalar_t__ dyn_adc_switch; } ;
struct alc_spec {scalar_t__ inv_dmic_pin; TYPE_1__ gen; scalar_t__ inv_dmic_muted; int /*<<< orphan*/  inv_dmic_fixup; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_inv_dmic_sync_adc (struct hda_codec*,int) ; 

__attribute__((used)) static void alc_inv_dmic_sync(struct hda_codec *codec, bool force)
{
	struct alc_spec *spec = codec->spec;
	int src, nums;

	if (!spec->inv_dmic_fixup)
		return;
	if (!spec->inv_dmic_muted && !force)
		return;
	nums = spec->gen.dyn_adc_switch ? 1 : spec->gen.num_adc_nids;
	for (src = 0; src < nums; src++) {
		bool dmic_fixup = false;

		if (spec->inv_dmic_muted &&
		    spec->gen.imux_pins[spec->gen.cur_mux[src]] == spec->inv_dmic_pin)
			dmic_fixup = true;
		if (!dmic_fixup && !force)
			continue;
		alc_inv_dmic_sync_adc(codec, src);
	}
}