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
struct snd_soc_codec {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {unsigned short* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 unsigned short AMS_DELTA_AGC ; 
 unsigned short AMS_DELTA_EARPIECE ; 
 unsigned short AMS_DELTA_MICROPHONE ; 
 unsigned short AMS_DELTA_MOUTHPIECE ; 
 unsigned short AMS_DELTA_SPEAKER ; 
 unsigned short ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned short ams_delta_audio_agc ; 
 int /*<<< orphan*/  ams_delta_audio_mode ; 
 unsigned short* ams_delta_audio_mode_pins ; 
 struct snd_soc_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned short snd_soc_dapm_get_pin_status (struct snd_soc_codec*,char*) ; 

__attribute__((used)) static int ams_delta_get_audio_mode(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec =  snd_kcontrol_chip(kcontrol);
	unsigned short pins, mode;

	pins = ((snd_soc_dapm_get_pin_status(codec, "Mouthpiece") <<
							AMS_DELTA_MOUTHPIECE) |
			(snd_soc_dapm_get_pin_status(codec, "Earpiece") <<
							AMS_DELTA_EARPIECE));
	if (pins)
		pins |= (snd_soc_dapm_get_pin_status(codec, "Microphone") <<
							AMS_DELTA_MICROPHONE);
	else
		pins = ((snd_soc_dapm_get_pin_status(codec, "Microphone") <<
							AMS_DELTA_MICROPHONE) |
			(snd_soc_dapm_get_pin_status(codec, "Speaker") <<
							AMS_DELTA_SPEAKER) |
			(ams_delta_audio_agc << AMS_DELTA_AGC));

	for (mode = 0; mode < ARRAY_SIZE(ams_delta_audio_mode); mode++)
		if (pins == ams_delta_audio_mode_pins[mode])
			break;

	if (mode >= ARRAY_SIZE(ams_delta_audio_mode))
		return -EINVAL;

	ucontrol->value.enumerated.item[0] = mode;

	return 0;
}