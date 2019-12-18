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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 unsigned char PRO_RATE_DEFAULT ; 

__attribute__((used)) static int snd_ice1712_pro_internal_clock_default_put(struct snd_kcontrol *kcontrol,
						      struct snd_ctl_elem_value *ucontrol)
{
	static const unsigned int xrate[13] = {
		8000, 9600, 11025, 12000, 16000, 22050, 24000,
		32000, 44100, 48000, 64000, 88200, 96000
	};
	unsigned char oval;
	int change = 0;

	oval = PRO_RATE_DEFAULT;
	PRO_RATE_DEFAULT = xrate[ucontrol->value.integer.value[0] % 13];
	change = PRO_RATE_DEFAULT != oval;

	return change;
}