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
struct hda_gen_spec {int* dyn_adc_idx; int /*<<< orphan*/ * adc_nids; scalar_t__ dyn_adc_switch; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */

__attribute__((used)) static hda_nid_t get_adc_nid(struct hda_codec *codec, int adc_idx, int imux_idx)
{
	struct hda_gen_spec *spec = codec->spec;
	if (spec->dyn_adc_switch)
		adc_idx = spec->dyn_adc_idx[imux_idx];
	return spec->adc_nids[adc_idx];
}