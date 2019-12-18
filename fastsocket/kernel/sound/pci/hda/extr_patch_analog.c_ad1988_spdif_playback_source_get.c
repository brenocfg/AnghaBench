#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {unsigned int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_AMP_GET_INPUT ; 
 int /*<<< orphan*/  AC_VERB_GET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  AC_VERB_GET_CONNECT_SEL ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int ad1988_spdif_playback_source_get(struct snd_kcontrol *kcontrol,
					    struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	unsigned int sel;

	sel = snd_hda_codec_read(codec, 0x1d, 0, AC_VERB_GET_AMP_GAIN_MUTE,
				 AC_AMP_GET_INPUT);
	if (!(sel & 0x80))
		ucontrol->value.enumerated.item[0] = 0;
	else {
		sel = snd_hda_codec_read(codec, 0x0b, 0,
					 AC_VERB_GET_CONNECT_SEL, 0);
		if (sel < 3)
			sel++;
		else
			sel = 0;
		ucontrol->value.enumerated.item[0] = sel;
	}
	return 0;
}