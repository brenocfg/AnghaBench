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
struct TYPE_4__ {void* unsol_event; void* init; } ;
struct hda_codec {TYPE_2__ patch_ops; struct conexant_spec* spec; } ;
struct TYPE_3__ {int max_channels; int /*<<< orphan*/  dig_out_nid; void* dac_nids; void* num_dacs; } ;
struct conexant_spec {int dell_automute; int num_adc_nids; int num_init_verbs; int hp_laptop; int asus; int mic_boost; int dell_vostro; int ideapad; int thinkpad; scalar_t__ beep_amp; int /*<<< orphan*/ * input_mux; TYPE_1__ multiout; void* port_d_mode; int /*<<< orphan*/ * init_verbs; int /*<<< orphan*/  num_mixers; void** mixers; int /*<<< orphan*/  capture_cleanup; int /*<<< orphan*/  capture_prepare; scalar_t__ cur_adc_idx; scalar_t__ cur_adc; void* channel_mode; void* num_channel_mode; int /*<<< orphan*/  capsrc_nids; int /*<<< orphan*/  adc_nids; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
#define  CXT5066_ASUS 135 
 int CXT5066_AUTO ; 
#define  CXT5066_DELL_LAPTOP 134 
#define  CXT5066_DELL_VOSTRO 133 
#define  CXT5066_HP_LAPTOP 132 
#define  CXT5066_IDEAPAD 131 
#define  CXT5066_LAPTOP 130 
 int /*<<< orphan*/  CXT5066_MODELS ; 
#define  CXT5066_OLPC_XO_1_5 129 
#define  CXT5066_THINKPAD 128 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 void* PIN_HP ; 
 void* PIN_OUT ; 
 int /*<<< orphan*/  conexant_check_dig_outs (struct hda_codec*,void*,void*) ; 
 void* conexant_init ; 
 TYPE_2__ conexant_patch_ops ; 
 int /*<<< orphan*/  cxt5066_adc_nids ; 
 int /*<<< orphan*/  cxt5066_capsrc_nids ; 
 int /*<<< orphan*/  cxt5066_capture_source ; 
 int /*<<< orphan*/  cxt5066_cfg_tbl ; 
 void* cxt5066_dac_nids ; 
 void* cxt5066_digout_pin_nids ; 
 void* cxt5066_init ; 
 int /*<<< orphan*/  cxt5066_init_verbs ; 
 int /*<<< orphan*/  cxt5066_init_verbs_hp_laptop ; 
 int /*<<< orphan*/  cxt5066_init_verbs_ideapad ; 
 int /*<<< orphan*/  cxt5066_init_verbs_olpc ; 
 int /*<<< orphan*/  cxt5066_init_verbs_portd_lo ; 
 int /*<<< orphan*/  cxt5066_init_verbs_thinkpad ; 
 int /*<<< orphan*/  cxt5066_init_verbs_vostro ; 
 void* cxt5066_mixer_master ; 
 void* cxt5066_mixer_master_olpc ; 
 void* cxt5066_mixer_olpc_dc ; 
 void* cxt5066_mixers ; 
 int /*<<< orphan*/  cxt5066_models ; 
 void* cxt5066_modes ; 
 int /*<<< orphan*/  cxt5066_olpc_capture_cleanup ; 
 int /*<<< orphan*/  cxt5066_olpc_capture_prepare ; 
 void* cxt5066_olpc_init ; 
 void* cxt5066_olpc_unsol_event ; 
 void* cxt5066_unsol_event ; 
 void* cxt5066_vostro_mixers ; 
 int /*<<< orphan*/  get_amp_nid_ (scalar_t__) ; 
 struct conexant_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int patch_conexant_auto (struct hda_codec*) ; 
 int /*<<< orphan*/  set_beep_amp (struct conexant_spec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_attach_beep_device (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_check_board_config (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_cxt5066(struct hda_codec *codec)
{
	struct conexant_spec *spec;
	int board_config;

	board_config = snd_hda_check_board_config(codec, CXT5066_MODELS,
						  cxt5066_models, cxt5066_cfg_tbl);
	if (board_config < 0)
		board_config = CXT5066_AUTO; /* model=auto as default */
	if (board_config == CXT5066_AUTO)
		return patch_conexant_auto(codec);

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	codec->spec = spec;

	codec->patch_ops = conexant_patch_ops;
	codec->patch_ops.init = conexant_init;

	spec->dell_automute = 0;
	spec->multiout.max_channels = 2;
	spec->multiout.num_dacs = ARRAY_SIZE(cxt5066_dac_nids);
	spec->multiout.dac_nids = cxt5066_dac_nids;
	conexant_check_dig_outs(codec, cxt5066_digout_pin_nids,
	    ARRAY_SIZE(cxt5066_digout_pin_nids));
	spec->num_adc_nids = 1;
	spec->adc_nids = cxt5066_adc_nids;
	spec->capsrc_nids = cxt5066_capsrc_nids;
	spec->input_mux = &cxt5066_capture_source;

	spec->port_d_mode = PIN_HP;

	spec->num_init_verbs = 1;
	spec->init_verbs[0] = cxt5066_init_verbs;
	spec->num_channel_mode = ARRAY_SIZE(cxt5066_modes);
	spec->channel_mode = cxt5066_modes;
	spec->cur_adc = 0;
	spec->cur_adc_idx = 0;

	set_beep_amp(spec, 0x13, 0, HDA_OUTPUT);

	switch (board_config) {
	default:
	case CXT5066_LAPTOP:
		spec->mixers[spec->num_mixers++] = cxt5066_mixer_master;
		spec->mixers[spec->num_mixers++] = cxt5066_mixers;
		break;
	case CXT5066_DELL_LAPTOP:
		spec->mixers[spec->num_mixers++] = cxt5066_mixer_master;
		spec->mixers[spec->num_mixers++] = cxt5066_mixers;

		spec->port_d_mode = PIN_OUT;
		spec->init_verbs[spec->num_init_verbs] = cxt5066_init_verbs_portd_lo;
		spec->num_init_verbs++;
		spec->dell_automute = 1;
		break;
	case CXT5066_ASUS:
	case CXT5066_HP_LAPTOP:
		codec->patch_ops.init = cxt5066_init;
		codec->patch_ops.unsol_event = cxt5066_unsol_event;
		spec->init_verbs[spec->num_init_verbs] =
			cxt5066_init_verbs_hp_laptop;
		spec->num_init_verbs++;
		spec->hp_laptop = board_config == CXT5066_HP_LAPTOP;
		spec->asus = board_config == CXT5066_ASUS;
		spec->mixers[spec->num_mixers++] = cxt5066_mixer_master;
		spec->mixers[spec->num_mixers++] = cxt5066_mixers;
		/* no S/PDIF out */
		if (board_config == CXT5066_HP_LAPTOP)
			spec->multiout.dig_out_nid = 0;
		/* input source automatically selected */
		spec->input_mux = NULL;
		spec->port_d_mode = 0;
		spec->mic_boost = 3; /* default 30dB gain */
		break;

	case CXT5066_OLPC_XO_1_5:
		codec->patch_ops.init = cxt5066_olpc_init;
		codec->patch_ops.unsol_event = cxt5066_olpc_unsol_event;
		spec->init_verbs[0] = cxt5066_init_verbs_olpc;
		spec->mixers[spec->num_mixers++] = cxt5066_mixer_master_olpc;
		spec->mixers[spec->num_mixers++] = cxt5066_mixer_olpc_dc;
		spec->mixers[spec->num_mixers++] = cxt5066_mixers;
		spec->port_d_mode = 0;
		spec->mic_boost = 3; /* default 30dB gain */

		/* no S/PDIF out */
		spec->multiout.dig_out_nid = 0;

		/* input source automatically selected */
		spec->input_mux = NULL;

		/* our capture hooks which allow us to turn on the microphone LED
		 * at the right time */
		spec->capture_prepare = cxt5066_olpc_capture_prepare;
		spec->capture_cleanup = cxt5066_olpc_capture_cleanup;
		break;
	case CXT5066_DELL_VOSTRO:
		codec->patch_ops.init = cxt5066_init;
		codec->patch_ops.unsol_event = cxt5066_unsol_event;
		spec->init_verbs[0] = cxt5066_init_verbs_vostro;
		spec->mixers[spec->num_mixers++] = cxt5066_mixer_master_olpc;
		spec->mixers[spec->num_mixers++] = cxt5066_mixers;
		spec->mixers[spec->num_mixers++] = cxt5066_vostro_mixers;
		spec->port_d_mode = 0;
		spec->dell_vostro = 1;
		spec->mic_boost = 3; /* default 30dB gain */

		/* no S/PDIF out */
		spec->multiout.dig_out_nid = 0;

		/* input source automatically selected */
		spec->input_mux = NULL;
		break;
	case CXT5066_IDEAPAD:
		codec->patch_ops.init = cxt5066_init;
		codec->patch_ops.unsol_event = cxt5066_unsol_event;
		spec->mixers[spec->num_mixers++] = cxt5066_mixer_master;
		spec->mixers[spec->num_mixers++] = cxt5066_mixers;
		spec->init_verbs[0] = cxt5066_init_verbs_ideapad;
		spec->port_d_mode = 0;
		spec->ideapad = 1;
		spec->mic_boost = 2;	/* default 20dB gain */

		/* no S/PDIF out */
		spec->multiout.dig_out_nid = 0;

		/* input source automatically selected */
		spec->input_mux = NULL;
		break;
	case CXT5066_THINKPAD:
		codec->patch_ops.init = cxt5066_init;
		codec->patch_ops.unsol_event = cxt5066_unsol_event;
		spec->mixers[spec->num_mixers++] = cxt5066_mixer_master;
		spec->mixers[spec->num_mixers++] = cxt5066_mixers;
		spec->init_verbs[0] = cxt5066_init_verbs_thinkpad;
		spec->thinkpad = 1;
		spec->port_d_mode = PIN_OUT;
		spec->mic_boost = 2;	/* default 20dB gain */

		/* no S/PDIF out */
		spec->multiout.dig_out_nid = 0;

		/* input source automatically selected */
		spec->input_mux = NULL;
		break;
	}

	if (spec->beep_amp)
		snd_hda_attach_beep_device(codec, get_amp_nid_(spec->beep_amp));

	return 0;
}