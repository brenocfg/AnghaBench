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
struct hda_jack_tbl {int jack_dirty; scalar_t__ gated_jack; int /*<<< orphan*/  pin_sense; scalar_t__ gating_jack; int /*<<< orphan*/  nid; scalar_t__ phantom_jack; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PINSENSE_PRESENCE ; 
 int /*<<< orphan*/  read_pin_sense (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_jack_detect (struct hda_codec*,scalar_t__) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_get (struct hda_codec*,scalar_t__) ; 

__attribute__((used)) static void jack_detect_update(struct hda_codec *codec,
			       struct hda_jack_tbl *jack)
{
	if (!jack->jack_dirty)
		return;

	if (jack->phantom_jack)
		jack->pin_sense = AC_PINSENSE_PRESENCE;
	else
		jack->pin_sense = read_pin_sense(codec, jack->nid);

	/* A gating jack indicates the jack is invalid if gating is unplugged */
	if (jack->gating_jack && !snd_hda_jack_detect(codec, jack->gating_jack))
		jack->pin_sense &= ~AC_PINSENSE_PRESENCE;

	jack->jack_dirty = 0;

	/* If a jack is gated by this one update it. */
	if (jack->gated_jack) {
		struct hda_jack_tbl *gated =
			snd_hda_jack_tbl_get(codec, jack->gated_jack);
		if (gated) {
			gated->jack_dirty = 1;
			jack_detect_update(codec, gated);
		}
	}
}