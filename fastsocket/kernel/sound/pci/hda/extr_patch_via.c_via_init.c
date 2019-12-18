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
struct via_spec {int num_iverbs; int /*<<< orphan*/ * init_verbs; } ;
struct hda_codec {struct via_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  __analog_low_current_mode (struct hda_codec*,int) ; 
 int /*<<< orphan*/  set_widgets_power_state (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_gen_init (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt1708_update_hp_work (struct hda_codec*) ; 

__attribute__((used)) static int via_init(struct hda_codec *codec)
{
	struct via_spec *spec = codec->spec;
	int i;

	for (i = 0; i < spec->num_iverbs; i++)
		snd_hda_sequence_write(codec, spec->init_verbs[i]);

	/* init power states */
	set_widgets_power_state(codec);
	__analog_low_current_mode(codec, true);

	snd_hda_gen_init(codec);

	vt1708_update_hp_work(codec);

	return 0;
}