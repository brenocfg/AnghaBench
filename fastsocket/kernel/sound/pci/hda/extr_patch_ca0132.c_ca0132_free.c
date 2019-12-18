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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int /*<<< orphan*/  base_exit_verbs; int /*<<< orphan*/  unsol_hp_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ca0132_exit_chip (struct hda_codec*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ca0132_spec*) ; 
 int /*<<< orphan*/  snd_hda_power_down (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_power_up (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca0132_free(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;

	cancel_delayed_work_sync(&spec->unsol_hp_work);
	snd_hda_power_up(codec);
	snd_hda_sequence_write(codec, spec->base_exit_verbs);
	ca0132_exit_chip(codec);
	snd_hda_power_down(codec);
	kfree(codec->spec);
}