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
struct hda_codec {int no_trigger_sense; int no_sticky_stream; int /*<<< orphan*/  patch_ops; struct ad198x_spec* spec; } ;
struct TYPE_4__ {int /*<<< orphan*/  amplist; } ;
struct TYPE_3__ {int max_channels; int /*<<< orphan*/  dig_out_nid; void* dac_nids; void* num_dacs; } ;
struct ad198x_spec {int num_mixers; int num_init_verbs; int vmaster_nid; int avoid_init_slave_vol; int /*<<< orphan*/  slave_vols; TYPE_2__ loopback; scalar_t__ spdif_route; int /*<<< orphan*/ * init_verbs; int /*<<< orphan*/ * mixers; int /*<<< orphan*/ * input_mux; int /*<<< orphan*/  capsrc_nids; void* adc_nids; void* num_adc_nids; TYPE_1__ multiout; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1884_SPDIF_OUT ; 
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 void* ad1884_adc_nids ; 
 int /*<<< orphan*/  ad1884_base_mixers ; 
 int /*<<< orphan*/  ad1884_capsrc_nids ; 
 int /*<<< orphan*/  ad1884_capture_source ; 
 void* ad1884_dac_nids ; 
 int /*<<< orphan*/  ad1884_init_verbs ; 
 int /*<<< orphan*/  ad1884_loopbacks ; 
 int /*<<< orphan*/  ad1884_slave_vols ; 
 int /*<<< orphan*/  ad198x_free (struct hda_codec*) ; 
 int /*<<< orphan*/  ad198x_patch_ops ; 
 int alloc_ad_spec (struct hda_codec*) ; 
 int /*<<< orphan*/  set_beep_amp (struct ad198x_spec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_hda_attach_beep_device (struct hda_codec*,int) ; 

__attribute__((used)) static int patch_ad1884_basic(struct hda_codec *codec)
{
	struct ad198x_spec *spec;
	int err;

	err = alloc_ad_spec(codec);
	if (err < 0)
		return err;
	spec = codec->spec;

	err = snd_hda_attach_beep_device(codec, 0x10);
	if (err < 0) {
		ad198x_free(codec);
		return err;
	}
	set_beep_amp(spec, 0x10, 0, HDA_OUTPUT);

	spec->multiout.max_channels = 2;
	spec->multiout.num_dacs = ARRAY_SIZE(ad1884_dac_nids);
	spec->multiout.dac_nids = ad1884_dac_nids;
	spec->multiout.dig_out_nid = AD1884_SPDIF_OUT;
	spec->num_adc_nids = ARRAY_SIZE(ad1884_adc_nids);
	spec->adc_nids = ad1884_adc_nids;
	spec->capsrc_nids = ad1884_capsrc_nids;
	spec->input_mux = &ad1884_capture_source;
	spec->num_mixers = 1;
	spec->mixers[0] = ad1884_base_mixers;
	spec->num_init_verbs = 1;
	spec->init_verbs[0] = ad1884_init_verbs;
	spec->spdif_route = 0;
#ifdef CONFIG_PM
	spec->loopback.amplist = ad1884_loopbacks;
#endif
	spec->vmaster_nid = 0x04;
	/* we need to cover all playback volumes */
	spec->slave_vols = ad1884_slave_vols;
	/* slaves may contain input volumes, so we can't raise to 0dB blindly */
	spec->avoid_init_slave_vol = 1;

	codec->patch_ops = ad198x_patch_ops;

	codec->no_trigger_sense = 1;
	codec->no_sticky_stream = 1;

	return 0;
}