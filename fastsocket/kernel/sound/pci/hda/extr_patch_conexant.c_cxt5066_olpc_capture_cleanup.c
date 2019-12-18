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
struct hda_verb {int member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {scalar_t__ recording; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,struct hda_verb const*) ; 

__attribute__((used)) static void cxt5066_olpc_capture_cleanup(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	const struct hda_verb disable_mics[] = {
		/* disable external mic, port B */
		{0x1a, AC_VERB_SET_PIN_WIDGET_CONTROL, 0},

		/* disble internal mic, port C */
		{0x1b, AC_VERB_SET_PIN_WIDGET_CONTROL, 0},

		/* disable DC capture, port F */
		{0x1e, AC_VERB_SET_PIN_WIDGET_CONTROL, 0},
		{},
	};

	snd_hda_sequence_write(codec, disable_mics);
	spec->recording = 0;
}