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
struct hda_gen_spec {int num_adc_nids; int num_all_adcs; scalar_t__* adc_nids; int /*<<< orphan*/  all_adcs; } ;
struct hda_codec {int num_nodes; scalar_t__ start_nid; struct hda_gen_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 unsigned int AC_WCAP_DIGITAL ; 
 int AC_WID_AUD_IN ; 
 int ARRAY_SIZE (scalar_t__*) ; 
 unsigned int get_wcaps (struct hda_codec*,scalar_t__) ; 
 int get_wcaps_type (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int fill_adc_nids(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	hda_nid_t nid;
	hda_nid_t *adc_nids = spec->adc_nids;
	int max_nums = ARRAY_SIZE(spec->adc_nids);
	int i, nums = 0;

	nid = codec->start_nid;
	for (i = 0; i < codec->num_nodes; i++, nid++) {
		unsigned int caps = get_wcaps(codec, nid);
		int type = get_wcaps_type(caps);

		if (type != AC_WID_AUD_IN || (caps & AC_WCAP_DIGITAL))
			continue;
		adc_nids[nums] = nid;
		if (++nums >= max_nums)
			break;
	}
	spec->num_adc_nids = nums;

	/* copy the detected ADCs to all_adcs[] */
	spec->num_all_adcs = nums;
	memcpy(spec->all_adcs, spec->adc_nids, nums * sizeof(hda_nid_t));

	return nums;
}