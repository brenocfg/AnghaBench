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
struct hda_codec {int /*<<< orphan*/  patch_ops; struct ca0132_spec* spec; } ;
struct ca0132_spec {int num_mixers; int num_init_verbs; int /*<<< orphan*/  autocfg; int /*<<< orphan*/  unsol_hp_work; int /*<<< orphan*/ * init_verbs; int /*<<< orphan*/  base_exit_verbs; int /*<<< orphan*/  base_init_verbs; int /*<<< orphan*/ * mixers; struct hda_codec* codec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ca0132_base_exit_verbs ; 
 int /*<<< orphan*/  ca0132_base_init_verbs ; 
 int /*<<< orphan*/  ca0132_config (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_init_chip (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_init_verbs0 ; 
 int /*<<< orphan*/  ca0132_init_verbs1 ; 
 int /*<<< orphan*/  ca0132_mixer ; 
 int /*<<< orphan*/  ca0132_patch_ops ; 
 int /*<<< orphan*/  ca0132_unsol_hp_delayed ; 
 struct ca0132_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int snd_hda_parse_pin_def_config (struct hda_codec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 

__attribute__((used)) static int patch_ca0132(struct hda_codec *codec)
{
	struct ca0132_spec *spec;
	int err;

	snd_printdd("patch_ca0132\n");

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	codec->spec = spec;
	spec->codec = codec;

	spec->num_mixers = 1;
	spec->mixers[0] = ca0132_mixer;

	spec->base_init_verbs = ca0132_base_init_verbs;
	spec->base_exit_verbs = ca0132_base_exit_verbs;
	spec->init_verbs[0] = ca0132_init_verbs0;
	spec->init_verbs[1] = ca0132_init_verbs1;
	spec->num_init_verbs = 2;

	INIT_DELAYED_WORK(&spec->unsol_hp_work, ca0132_unsol_hp_delayed);

	ca0132_init_chip(codec);

	ca0132_config(codec);

	err = snd_hda_parse_pin_def_config(codec, &spec->autocfg, NULL);
	if (err < 0)
		return err;

	codec->patch_ops = ca0132_patch_ops;

	return 0;
}