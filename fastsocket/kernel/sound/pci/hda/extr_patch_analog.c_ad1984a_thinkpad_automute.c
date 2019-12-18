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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_AMP_MUTE ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int /*<<< orphan*/  snd_hda_codec_amp_stereo (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_jack_detect (struct hda_codec*,int) ; 

__attribute__((used)) static void ad1984a_thinkpad_automute(struct hda_codec *codec)
{
	unsigned int present;

	present = snd_hda_jack_detect(codec, 0x11);
	snd_hda_codec_amp_stereo(codec, 0x12, HDA_OUTPUT, 0,
				 HDA_AMP_MUTE, present ? HDA_AMP_MUTE : 0);
}