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
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {int /*<<< orphan*/  cur_eapd; scalar_t__ hp_present; } ;

/* Variables and functions */
 unsigned int HDA_AMP_MUTE ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int /*<<< orphan*/  snd_hda_codec_amp_stereo (struct hda_codec*,int,int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 
 scalar_t__ snd_hda_jack_detect (struct hda_codec*,int) ; 

__attribute__((used)) static void cxt5047_hp_automute(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	unsigned int bits;

	spec->hp_present = snd_hda_jack_detect(codec, 0x13);

	bits = (spec->hp_present || !spec->cur_eapd) ? HDA_AMP_MUTE : 0;
	/* See the note in cxt5047_hp_master_sw_put */
	snd_hda_codec_amp_stereo(codec, 0x1d, HDA_OUTPUT, 0x01,
				 HDA_AMP_MUTE, bits);
}