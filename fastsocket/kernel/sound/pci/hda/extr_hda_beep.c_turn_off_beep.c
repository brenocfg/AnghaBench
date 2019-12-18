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
struct hda_beep {int /*<<< orphan*/  codec; scalar_t__ playing; int /*<<< orphan*/  nid; int /*<<< orphan*/  beep_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_BEEP_CONTROL ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_codec_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_power_down (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void turn_off_beep(struct hda_beep *beep)
{
	cancel_work_sync(&beep->beep_work);
	if (beep->playing) {
		/* turn off beep */
		snd_hda_codec_write(beep->codec, beep->nid, 0,
				    AC_VERB_SET_BEEP_CONTROL, 0);
		beep->playing = 0;
		snd_hda_power_down(beep->codec);
	}
}