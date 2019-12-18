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
struct hda_codec {struct hda_beep* beep; } ;
struct hda_beep {scalar_t__ dev; int /*<<< orphan*/  unregister_work; int /*<<< orphan*/  register_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hda_beep*) ; 
 int /*<<< orphan*/  snd_hda_do_detach (struct hda_beep*) ; 

void snd_hda_detach_beep_device(struct hda_codec *codec)
{
	struct hda_beep *beep = codec->beep;
	if (beep) {
		cancel_work_sync(&beep->register_work);
		cancel_delayed_work(&beep->unregister_work);
		if (beep->dev)
			snd_hda_do_detach(beep);
		codec->beep = NULL;
		kfree(beep);
	}
}