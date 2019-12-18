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
struct via82xx {unsigned char* playback_volume_c; int port; unsigned char** playback_volume; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {unsigned char* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 unsigned char VIA_DXS_MAX_VOLUME ; 
 scalar_t__ VIA_REG_OFS_PLAYBACK_VOLUME_L ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 struct via82xx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_via8233_pcmdxs_volume_put(struct snd_kcontrol *kcontrol,
					 struct snd_ctl_elem_value *ucontrol)
{
	struct via82xx *chip = snd_kcontrol_chip(kcontrol);
	unsigned int idx;
	unsigned char val;
	int i, change = 0;

	for (i = 0; i < 2; i++) {
		val = ucontrol->value.integer.value[i];
		if (val > VIA_DXS_MAX_VOLUME)
			val = VIA_DXS_MAX_VOLUME;
		val = VIA_DXS_MAX_VOLUME - val;
		if (val != chip->playback_volume_c[i]) {
			change = 1;
			chip->playback_volume_c[i] = val;
			for (idx = 0; idx < 4; idx++) {
				unsigned long port = chip->port + 0x10 * idx;
				chip->playback_volume[idx][i] = val;
				outb(val, port + VIA_REG_OFS_PLAYBACK_VOLUME_L + i);
			}
		}
	}
	return change;
}