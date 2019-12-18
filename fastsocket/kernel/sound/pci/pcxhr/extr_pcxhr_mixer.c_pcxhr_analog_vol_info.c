#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcxhr {TYPE_1__* mgr; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_5__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_3__ value; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {scalar_t__ is_hr_stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  HR222_LINE_CAPTURE_LEVEL_MAX ; 
 int /*<<< orphan*/  HR222_LINE_CAPTURE_LEVEL_MIN ; 
 int /*<<< orphan*/  HR222_LINE_PLAYBACK_LEVEL_MAX ; 
 int /*<<< orphan*/  HR222_LINE_PLAYBACK_LEVEL_MIN ; 
 int /*<<< orphan*/  PCXHR_LINE_CAPTURE_LEVEL_MAX ; 
 int /*<<< orphan*/  PCXHR_LINE_CAPTURE_LEVEL_MIN ; 
 int /*<<< orphan*/  PCXHR_LINE_PLAYBACK_LEVEL_MAX ; 
 int /*<<< orphan*/  PCXHR_LINE_PLAYBACK_LEVEL_MIN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 struct snd_pcxhr* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int pcxhr_analog_vol_info(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_info *uinfo)
{
	struct snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	if (kcontrol->private_value == 0) {	/* playback */
	    if (chip->mgr->is_hr_stereo) {
		uinfo->value.integer.min =
			HR222_LINE_PLAYBACK_LEVEL_MIN;	/* -25 dB */
		uinfo->value.integer.max =
			HR222_LINE_PLAYBACK_LEVEL_MAX;	/* +24 dB */
	    } else {
		uinfo->value.integer.min =
			PCXHR_LINE_PLAYBACK_LEVEL_MIN;	/*-104 dB */
		uinfo->value.integer.max =
			PCXHR_LINE_PLAYBACK_LEVEL_MAX;	/* +24 dB */
	    }
	} else {				/* capture */
	    if (chip->mgr->is_hr_stereo) {
		uinfo->value.integer.min =
			HR222_LINE_CAPTURE_LEVEL_MIN;	/*-112 dB */
		uinfo->value.integer.max =
			HR222_LINE_CAPTURE_LEVEL_MAX;	/* +15.5 dB */
	    } else {
		uinfo->value.integer.min =
			PCXHR_LINE_CAPTURE_LEVEL_MIN;	/*-112 dB */
		uinfo->value.integer.max =
			PCXHR_LINE_CAPTURE_LEVEL_MAX;	/* +15.5 dB */
	    }
	}
	return 0;
}