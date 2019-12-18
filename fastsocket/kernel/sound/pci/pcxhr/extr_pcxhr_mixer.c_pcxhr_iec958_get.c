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
struct snd_pcxhr {unsigned char* aes_bits; TYPE_3__* mgr; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_4__ {unsigned char* status; } ;
struct TYPE_5__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  mixer_mutex; scalar_t__ is_hr_stereo; } ;

/* Variables and functions */
 int hr222_iec958_capture_byte (struct snd_pcxhr*,int,unsigned char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pcxhr_iec958_capture_byte (struct snd_pcxhr*,int,unsigned char*) ; 
 struct snd_pcxhr* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int pcxhr_iec958_get(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	unsigned char aes_bits;
	int i, err;

	mutex_lock(&chip->mgr->mixer_mutex);
	for(i = 0; i < 5; i++) {
		if (kcontrol->private_value == 0)	/* playback */
			aes_bits = chip->aes_bits[i];
		else {				/* capture */
			if (chip->mgr->is_hr_stereo)
				err = hr222_iec958_capture_byte(chip, i,
								&aes_bits);
			else
				err = pcxhr_iec958_capture_byte(chip, i,
								&aes_bits);
			if (err)
				break;
		}
		ucontrol->value.iec958.status[i] = aes_bits;
	}
	mutex_unlock(&chip->mgr->mixer_mutex);
        return 0;
}