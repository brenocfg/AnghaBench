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
struct snd_trident_pcm_mixer {int pan; } ;
struct snd_trident {struct snd_trident_pcm_mixer* pcm_mixer; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 size_t snd_ctl_get_ioffnum (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_trident* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_trident_pcm_pan_control_get(struct snd_kcontrol *kcontrol,
					   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_trident *trident = snd_kcontrol_chip(kcontrol);
	struct snd_trident_pcm_mixer *mix = &trident->pcm_mixer[snd_ctl_get_ioffnum(kcontrol, &ucontrol->id)];

	ucontrol->value.integer.value[0] = mix->pan;
	if (ucontrol->value.integer.value[0] & 0x40) {
		ucontrol->value.integer.value[0] = (0x3f - (ucontrol->value.integer.value[0] & 0x3f));
	} else {
		ucontrol->value.integer.value[0] |= 0x40;
	}
	return 0;
}