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
struct hda_verb {int member_0; int member_2; int /*<<< orphan*/  const member_1; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
#define  AC_VERB_SET_CONNECT_SEL 131 
#define  AC_VERB_SET_PIN_WIDGET_CONTROL 130 
#define  PIN_IN 129 
#define  PIN_VREF80 128 
 unsigned int snd_hda_jack_detect (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,struct hda_verb const*) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 

__attribute__((used)) static void cxt5066_thinkpad_automic(struct hda_codec *codec)
{
	unsigned int ext_present, dock_present;

	static const struct hda_verb ext_mic_present[] = {
		{0x14, AC_VERB_SET_CONNECT_SEL, 0},
		{0x17, AC_VERB_SET_CONNECT_SEL, 1},
		{0x1b, AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_VREF80},
		{0x23, AC_VERB_SET_PIN_WIDGET_CONTROL, 0},
		{0x1a, AC_VERB_SET_PIN_WIDGET_CONTROL, 0},
		{}
	};
	static const struct hda_verb dock_mic_present[] = {
		{0x14, AC_VERB_SET_CONNECT_SEL, 0},
		{0x17, AC_VERB_SET_CONNECT_SEL, 0},
		{0x1a, AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_VREF80},
		{0x23, AC_VERB_SET_PIN_WIDGET_CONTROL, 0},
		{0x1b, AC_VERB_SET_PIN_WIDGET_CONTROL, 0},
		{}
	};
	static const struct hda_verb ext_mic_absent[] = {
		{0x14, AC_VERB_SET_CONNECT_SEL, 2},
		{0x23, AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_IN},
		{0x1b, AC_VERB_SET_PIN_WIDGET_CONTROL, 0},
		{0x1a, AC_VERB_SET_PIN_WIDGET_CONTROL, 0},
		{}
	};

	ext_present = snd_hda_jack_detect(codec, 0x1b);
	dock_present = snd_hda_jack_detect(codec, 0x1a);
	if (ext_present) {
		snd_printdd("CXT5066: external microphone detected\n");
		snd_hda_sequence_write(codec, ext_mic_present);
	} else if (dock_present) {
		snd_printdd("CXT5066: dock microphone detected\n");
		snd_hda_sequence_write(codec, dock_mic_present);
	} else {
		snd_printdd("CXT5066: external microphone absent\n");
		snd_hda_sequence_write(codec, ext_mic_absent);
	}
}