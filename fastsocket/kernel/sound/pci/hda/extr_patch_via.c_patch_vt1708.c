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
struct TYPE_3__ {int mixer_nid; int suppress_auto_mic; int auto_mute_via_amp; } ;
struct via_spec {int vt1708_jack_detect; int /*<<< orphan*/  num_iverbs; int /*<<< orphan*/ * init_verbs; int /*<<< orphan*/  num_mixers; int /*<<< orphan*/ * mixers; TYPE_1__ gen; } ;
struct TYPE_4__ {int /*<<< orphan*/  build_pcms; int /*<<< orphan*/  build_controls; } ;
struct hda_codec {scalar_t__ jackpoll_interval; TYPE_2__ patch_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VT1708_CD_PIN_NID ; 
 int /*<<< orphan*/  VT1708_HP_PIN_NID ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  via_free (struct hda_codec*) ; 
 struct via_spec* via_new_spec (struct hda_codec*) ; 
 int via_parse_auto_config (struct hda_codec*) ; 
 TYPE_2__ via_patch_ops ; 
 int /*<<< orphan*/  vt1708_build_controls ; 
 int /*<<< orphan*/  vt1708_build_pcms ; 
 int /*<<< orphan*/  vt1708_init_verbs ; 
 int /*<<< orphan*/  vt1708_jack_detect_ctl ; 
 int /*<<< orphan*/  vt1708_set_pinconfig_connect (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_vt1708(struct hda_codec *codec)
{
	struct via_spec *spec;
	int err;

	/* create a codec specific record */
	spec = via_new_spec(codec);
	if (spec == NULL)
		return -ENOMEM;

	spec->gen.mixer_nid = 0x17;

	/* set jackpoll_interval while parsing the codec */
	codec->jackpoll_interval = msecs_to_jiffies(100);
	spec->vt1708_jack_detect = 1;

	/* don't support the input jack switching due to lack of unsol event */
	/* (it may work with polling, though, but it needs testing) */
	spec->gen.suppress_auto_mic = 1;
	/* Some machines show the broken speaker mute */
	spec->gen.auto_mute_via_amp = 1;

	/* Add HP and CD pin config connect bit re-config action */
	vt1708_set_pinconfig_connect(codec, VT1708_HP_PIN_NID);
	vt1708_set_pinconfig_connect(codec, VT1708_CD_PIN_NID);

	/* automatic parse from the BIOS config */
	err = via_parse_auto_config(codec);
	if (err < 0) {
		via_free(codec);
		return err;
	}

	/* add jack detect on/off control */
	spec->mixers[spec->num_mixers++] = vt1708_jack_detect_ctl;

	spec->init_verbs[spec->num_iverbs++] = vt1708_init_verbs;

	codec->patch_ops = via_patch_ops;
	codec->patch_ops.build_controls = vt1708_build_controls;
	codec->patch_ops.build_pcms = vt1708_build_pcms;

	/* clear jackpoll_interval again; it's set dynamically */
	codec->jackpoll_interval = 0;

	return 0;
}