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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int* vnode_lvol; int* vnode_rvol; int* effects_switch; scalar_t__ voicefx_val; scalar_t__* vnode_rswitch; scalar_t__* vnode_lswitch; scalar_t__ cur_mic_boost; int /*<<< orphan*/  cur_mic_type; int /*<<< orphan*/  cur_out_type; int /*<<< orphan*/  chipio_mutex; } ;
struct TYPE_2__ {scalar_t__* reqs; } ;

/* Variables and functions */
 size_t CRYSTAL_VOICE ; 
 int /*<<< orphan*/  DIGITAL_MIC ; 
 size_t EFFECT_START_NID ; 
 int IN_EFFECTS_COUNT ; 
 int OUT_EFFECTS_COUNT ; 
 size_t PLAY_ENHANCEMENT ; 
 int /*<<< orphan*/  SPEAKER_OUT ; 
 int VNODES_COUNT ; 
 TYPE_1__* ca0132_effects ; 
 int /*<<< orphan*/  ca0132_init_tuning_defaults (struct hda_codec*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ca0132_init_chip(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	int num_fx;
	int i;
	unsigned int on;

	mutex_init(&spec->chipio_mutex);

	spec->cur_out_type = SPEAKER_OUT;
	spec->cur_mic_type = DIGITAL_MIC;
	spec->cur_mic_boost = 0;

	for (i = 0; i < VNODES_COUNT; i++) {
		spec->vnode_lvol[i] = 0x5a;
		spec->vnode_rvol[i] = 0x5a;
		spec->vnode_lswitch[i] = 0;
		spec->vnode_rswitch[i] = 0;
	}

	/*
	 * Default states for effects are in ca0132_effects[].
	 */
	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT;
	for (i = 0; i < num_fx; i++) {
		on = (unsigned int)ca0132_effects[i].reqs[0];
		spec->effects_switch[i] = on ? 1 : 0;
	}

	spec->voicefx_val = 0;
	spec->effects_switch[PLAY_ENHANCEMENT - EFFECT_START_NID] = 1;
	spec->effects_switch[CRYSTAL_VOICE - EFFECT_START_NID] = 0;

#ifdef ENABLE_TUNING_CONTROLS
	ca0132_init_tuning_defaults(codec);
#endif
}