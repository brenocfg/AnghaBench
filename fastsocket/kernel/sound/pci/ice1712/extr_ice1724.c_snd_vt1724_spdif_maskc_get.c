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
struct TYPE_4__ {int* status; } ;
struct TYPE_3__ {TYPE_2__ iec958; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int IEC958_AES0_CON_EMPHASIS ; 
 int IEC958_AES0_CON_NOT_COPYRIGHT ; 
 int IEC958_AES0_NONAUDIO ; 
 int IEC958_AES0_PROFESSIONAL ; 
 int IEC958_AES1_CON_CATEGORY ; 
 int IEC958_AES1_CON_ORIGINAL ; 
 int IEC958_AES3_CON_FS ; 

__attribute__((used)) static int snd_vt1724_spdif_maskc_get(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_value *ucontrol)
{
	ucontrol->value.iec958.status[0] = IEC958_AES0_NONAUDIO |
						     IEC958_AES0_PROFESSIONAL |
						     IEC958_AES0_CON_NOT_COPYRIGHT |
						     IEC958_AES0_CON_EMPHASIS;
	ucontrol->value.iec958.status[1] = IEC958_AES1_CON_ORIGINAL |
						     IEC958_AES1_CON_CATEGORY;
	ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS;
	return 0;
}