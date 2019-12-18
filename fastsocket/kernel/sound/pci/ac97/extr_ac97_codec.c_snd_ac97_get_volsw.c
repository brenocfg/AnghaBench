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
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ac97_page_restore (struct snd_ac97*,int) ; 
 int snd_ac97_page_save (struct snd_ac97*,int,struct snd_kcontrol*) ; 
 int snd_ac97_read_cache (struct snd_ac97*,int) ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ac97_get_volsw(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	int reg = kcontrol->private_value & 0xff;
	int shift = (kcontrol->private_value >> 8) & 0x0f;
	int rshift = (kcontrol->private_value >> 12) & 0x0f;
	int mask = (kcontrol->private_value >> 16) & 0xff;
	int invert = (kcontrol->private_value >> 24) & 0x01;
	int page_save;

	page_save = snd_ac97_page_save(ac97, reg, kcontrol);
	ucontrol->value.integer.value[0] = (snd_ac97_read_cache(ac97, reg) >> shift) & mask;
	if (shift != rshift)
		ucontrol->value.integer.value[1] = (snd_ac97_read_cache(ac97, reg) >> rshift) & mask;
	if (invert) {
		ucontrol->value.integer.value[0] = mask - ucontrol->value.integer.value[0];
		if (shift != rshift)
			ucontrol->value.integer.value[1] = mask - ucontrol->value.integer.value[1];
	}
	snd_ac97_page_restore(ac97, page_save);
	return 0;
}