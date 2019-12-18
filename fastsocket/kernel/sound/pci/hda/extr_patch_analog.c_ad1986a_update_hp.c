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
struct hda_codec {struct ad198x_spec* spec; } ;
struct ad198x_spec {scalar_t__ jack_present; } ;

/* Variables and functions */
 unsigned int HDA_AMP_MUTE ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 unsigned int snd_hda_codec_amp_read (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_amp_stereo (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void ad1986a_update_hp(struct hda_codec *codec)
{
	struct ad198x_spec *spec = codec->spec;
	unsigned int mute;

	if (spec->jack_present)
		mute = HDA_AMP_MUTE; /* mute internal speaker */
	else
		/* unmute internal speaker if necessary */
		mute = snd_hda_codec_amp_read(codec, 0x1a, 0, HDA_OUTPUT, 0);
	snd_hda_codec_amp_stereo(codec, 0x1b, HDA_OUTPUT, 0,
				 HDA_AMP_MUTE, mute);
}