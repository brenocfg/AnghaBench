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
typedef  int ushort ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int snd_ac97_read (struct snd_ac97*,int) ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ac97_vt1617a_smart51_get(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	ushort usSM51, usMS;  

	struct snd_ac97 *pac97;
	
	pac97 = snd_kcontrol_chip(kcontrol); /* grab codec handle */

	/* grab our desired bits, then mash them together in a manner
	 * consistent with Table 6 on page 17 in the 1617a docs */
 
	usSM51 = snd_ac97_read(pac97, 0x7a) >> 14;
	usMS   = snd_ac97_read(pac97, 0x20) >> 8;
  
	ucontrol->value.enumerated.item[0] = (usSM51 << 1) + usMS;

	return 0;
}