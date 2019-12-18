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
struct hda_jack_tbl {int /*<<< orphan*/  (* callback ) (struct hda_codec*,struct hda_jack_tbl*) ;scalar_t__ gated_jack; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 struct hda_jack_tbl* snd_hda_jack_tbl_get (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*,struct hda_jack_tbl*) ; 
 int /*<<< orphan*/  stub2 (struct hda_codec*,struct hda_jack_tbl*) ; 

__attribute__((used)) static void call_jack_callback(struct hda_codec *codec,
			       struct hda_jack_tbl *jack)
{
	if (jack->callback)
		jack->callback(codec, jack);
	if (jack->gated_jack) {
		struct hda_jack_tbl *gated =
			snd_hda_jack_tbl_get(codec, jack->gated_jack);
		if (gated && gated->callback)
			gated->callback(codec, gated);
	}
}