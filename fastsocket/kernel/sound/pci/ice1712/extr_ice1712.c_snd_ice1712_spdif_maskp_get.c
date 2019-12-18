#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {scalar_t__ default_get; } ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct snd_ice1712 {TYPE_2__ spdif; } ;
struct TYPE_7__ {int* status; } ;
struct TYPE_8__ {TYPE_3__ iec958; } ;
struct snd_ctl_elem_value {TYPE_4__ value; } ;

/* Variables and functions */
 int IEC958_AES0_NONAUDIO ; 
 int IEC958_AES0_PROFESSIONAL ; 
 int IEC958_AES0_PRO_EMPHASIS ; 
 int IEC958_AES0_PRO_FS ; 
 int IEC958_AES1_PRO_MODE ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ice1712_spdif_maskp_get(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	if (ice->spdif.ops.default_get) {
		ucontrol->value.iec958.status[0] = IEC958_AES0_NONAUDIO |
						     IEC958_AES0_PROFESSIONAL |
						     IEC958_AES0_PRO_FS |
						     IEC958_AES0_PRO_EMPHASIS;
		ucontrol->value.iec958.status[1] = IEC958_AES1_PRO_MODE;
	} else {
		ucontrol->value.iec958.status[0] = 0xff;
		ucontrol->value.iec958.status[1] = 0xff;
		ucontrol->value.iec958.status[2] = 0xff;
		ucontrol->value.iec958.status[3] = 0xff;
		ucontrol->value.iec958.status[4] = 0xff;
	}
	return 0;
}