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
struct hda_verb {int member_0; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  const member_1; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
#define  AC_VERB_SET_AMP_GAIN_MUTE 130 
#define  AMP_OUT_MUTE 129 
#define  AMP_OUT_UNMUTE 128 
 unsigned int snd_hda_jack_detect (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,struct hda_verb const*) ; 

__attribute__((used)) static void cxt5047_hp_automic(struct hda_codec *codec)
{
	static const struct hda_verb mic_jack_on[] = {
		{0x15, AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_MUTE},
		{0x17, AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_UNMUTE},
		{}
	};
	static const struct hda_verb mic_jack_off[] = {
		{0x17, AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_MUTE},
		{0x15, AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_UNMUTE},
		{}
	};
	unsigned int present;

	present = snd_hda_jack_detect(codec, 0x15);
	if (present)
		snd_hda_sequence_write(codec, mic_jack_on);
	else
		snd_hda_sequence_write(codec, mic_jack_off);
}