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
struct TYPE_4__ {void* init; void* unsol_event; } ;
struct hda_codec {int single_adc_amp; int subsystem_id; TYPE_2__ patch_ops; struct conexant_spec* spec; } ;
struct TYPE_3__ {int max_channels; int /*<<< orphan*/  dig_out_nid; void* dac_nids; void* num_dacs; } ;
struct conexant_spec {int num_adc_nids; int num_mixers; int num_init_verbs; scalar_t__ beep_amp; void** init_verbs; void** mixers; int /*<<< orphan*/ * input_mux; void* channel_mode; void* num_channel_mode; scalar_t__ spdif_route; int /*<<< orphan*/  capsrc_nids; int /*<<< orphan*/  adc_nids; TYPE_1__ multiout; } ;

/* Variables and functions */
 int AC_AMPCAP_MUTE_SHIFT ; 
 int AC_AMPCAP_NUM_STEPS_SHIFT ; 
 int AC_AMPCAP_OFFSET_SHIFT ; 
 int AC_AMPCAP_STEP_SIZE_SHIFT ; 
 void* ARRAY_SIZE (void*) ; 
 int CXT5045_AUTO ; 
#define  CXT5045_BENQ 133 
#define  CXT5045_LAPTOP_HP530 132 
#define  CXT5045_LAPTOP_HPMICSENSE 131 
#define  CXT5045_LAPTOP_HPSENSE 130 
#define  CXT5045_LAPTOP_MICSENSE 129 
 int /*<<< orphan*/  CXT5045_MODELS ; 
 int /*<<< orphan*/  CXT5045_SPDIF_OUT ; 
#define  CXT5045_TEST 128 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 TYPE_2__ conexant_patch_ops ; 
 int /*<<< orphan*/  cxt5045_adc_nids ; 
 void* cxt5045_benq_init_verbs ; 
 void* cxt5045_benq_mixers ; 
 int /*<<< orphan*/  cxt5045_capsrc_nids ; 
 int /*<<< orphan*/  cxt5045_capture_source ; 
 int /*<<< orphan*/  cxt5045_capture_source_benq ; 
 int /*<<< orphan*/  cxt5045_capture_source_hp530 ; 
 int /*<<< orphan*/  cxt5045_cfg_tbl ; 
 void* cxt5045_dac_nids ; 
 void* cxt5045_hp_sense_init_verbs ; 
 void* cxt5045_hp_unsol_event ; 
 void* cxt5045_init ; 
 void* cxt5045_init_verbs ; 
 void* cxt5045_mic_sense_init_verbs ; 
 void* cxt5045_mixers ; 
 void* cxt5045_mixers_hp530 ; 
 int /*<<< orphan*/  cxt5045_models ; 
 void* cxt5045_modes ; 
 int /*<<< orphan*/  cxt5045_test_capture_source ; 
 void* cxt5045_test_init_verbs ; 
 void* cxt5045_test_mixer ; 
 int /*<<< orphan*/  get_amp_nid_ (scalar_t__) ; 
 struct conexant_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int patch_conexant_auto (struct hda_codec*) ; 
 int /*<<< orphan*/  set_beep_amp (struct conexant_spec*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_attach_beep_device (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_check_board_config (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_override_amp_caps (struct hda_codec*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int patch_cxt5045(struct hda_codec *codec)
{
	struct conexant_spec *spec;
	int board_config;

	board_config = snd_hda_check_board_config(codec, CXT5045_MODELS,
						  cxt5045_models,
						  cxt5045_cfg_tbl);
	if (board_config < 0)
		board_config = CXT5045_AUTO; /* model=auto as default */
	if (board_config == CXT5045_AUTO)
		return patch_conexant_auto(codec);

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	codec->spec = spec;
	codec->single_adc_amp = 1;

	spec->multiout.max_channels = 2;
	spec->multiout.num_dacs = ARRAY_SIZE(cxt5045_dac_nids);
	spec->multiout.dac_nids = cxt5045_dac_nids;
	spec->multiout.dig_out_nid = CXT5045_SPDIF_OUT;
	spec->num_adc_nids = 1;
	spec->adc_nids = cxt5045_adc_nids;
	spec->capsrc_nids = cxt5045_capsrc_nids;
	spec->input_mux = &cxt5045_capture_source;
	spec->num_mixers = 1;
	spec->mixers[0] = cxt5045_mixers;
	spec->num_init_verbs = 1;
	spec->init_verbs[0] = cxt5045_init_verbs;
	spec->spdif_route = 0;
	spec->num_channel_mode = ARRAY_SIZE(cxt5045_modes);
	spec->channel_mode = cxt5045_modes;

	set_beep_amp(spec, 0x16, 0, 1);

	codec->patch_ops = conexant_patch_ops;

	switch (board_config) {
	case CXT5045_LAPTOP_HPSENSE:
		codec->patch_ops.unsol_event = cxt5045_hp_unsol_event;
		spec->input_mux = &cxt5045_capture_source;
		spec->num_init_verbs = 2;
		spec->init_verbs[1] = cxt5045_hp_sense_init_verbs;
		spec->mixers[0] = cxt5045_mixers;
		codec->patch_ops.init = cxt5045_init;
		break;
	case CXT5045_LAPTOP_MICSENSE:
		codec->patch_ops.unsol_event = cxt5045_hp_unsol_event;
		spec->input_mux = &cxt5045_capture_source;
		spec->num_init_verbs = 2;
		spec->init_verbs[1] = cxt5045_mic_sense_init_verbs;
		spec->mixers[0] = cxt5045_mixers;
		codec->patch_ops.init = cxt5045_init;
		break;
	default:
	case CXT5045_LAPTOP_HPMICSENSE:
		codec->patch_ops.unsol_event = cxt5045_hp_unsol_event;
		spec->input_mux = &cxt5045_capture_source;
		spec->num_init_verbs = 3;
		spec->init_verbs[1] = cxt5045_hp_sense_init_verbs;
		spec->init_verbs[2] = cxt5045_mic_sense_init_verbs;
		spec->mixers[0] = cxt5045_mixers;
		codec->patch_ops.init = cxt5045_init;
		break;
	case CXT5045_BENQ:
		codec->patch_ops.unsol_event = cxt5045_hp_unsol_event;
		spec->input_mux = &cxt5045_capture_source_benq;
		spec->num_init_verbs = 1;
		spec->init_verbs[0] = cxt5045_benq_init_verbs;
		spec->mixers[0] = cxt5045_mixers;
		spec->mixers[1] = cxt5045_benq_mixers;
		spec->num_mixers = 2;
		codec->patch_ops.init = cxt5045_init;
		break;
	case CXT5045_LAPTOP_HP530:
		codec->patch_ops.unsol_event = cxt5045_hp_unsol_event;
		spec->input_mux = &cxt5045_capture_source_hp530;
		spec->num_init_verbs = 2;
		spec->init_verbs[1] = cxt5045_hp_sense_init_verbs;
		spec->mixers[0] = cxt5045_mixers_hp530;
		codec->patch_ops.init = cxt5045_init;
		break;
#ifdef CONFIG_SND_DEBUG
	case CXT5045_TEST:
		spec->input_mux = &cxt5045_test_capture_source;
		spec->mixers[0] = cxt5045_test_mixer;
		spec->init_verbs[0] = cxt5045_test_init_verbs;
		break;
		
#endif	
	}

	switch (codec->subsystem_id >> 16) {
	case 0x103c:
	case 0x1631:
	case 0x1734:
	case 0x17aa:
		/* HP, Packard Bell, Fujitsu-Siemens & Lenovo laptops have
		 * really bad sound over 0dB on NID 0x17. Fix max PCM level to
		 * 0 dB (originally it has 0x2b steps with 0dB offset 0x14)
		 */
		snd_hda_override_amp_caps(codec, 0x17, HDA_INPUT,
					  (0x14 << AC_AMPCAP_OFFSET_SHIFT) |
					  (0x14 << AC_AMPCAP_NUM_STEPS_SHIFT) |
					  (0x05 << AC_AMPCAP_STEP_SIZE_SHIFT) |
					  (1 << AC_AMPCAP_MUTE_SHIFT));
		break;
	}

	if (spec->beep_amp)
		snd_hda_attach_beep_device(codec, get_amp_nid_(spec->beep_amp));

	return 0;
}