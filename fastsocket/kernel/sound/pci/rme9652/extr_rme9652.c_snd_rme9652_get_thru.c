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
typedef  int u32 ;
struct snd_rme9652 {int thru_bits; unsigned int ss_channels; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct snd_rme9652* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_rme9652_get_thru(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	unsigned int k;
	u32 thru_bits = rme9652->thru_bits;

	for (k = 0; k < rme9652->ss_channels; ++k) {
		ucontrol->value.integer.value[k] = !!(thru_bits & (1 << k));
	}
	return 0;
}