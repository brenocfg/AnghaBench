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
struct snd_ice1712 {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int AUREON_AC97_STEREO ; 
 unsigned short aureon_ac97_read (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  aureon_ac97_write (struct snd_ice1712*,int,unsigned short) ; 
 int /*<<< orphan*/  snd_ice1712_restore_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int aureon_ac97_vol_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned short ovol, nvol;
	int change;

	snd_ice1712_save_gpio_status(ice);

	ovol = aureon_ac97_read(ice, kcontrol->private_value & 0x7F);
	nvol = (0x1F - ucontrol->value.integer.value[0]) & 0x001F;
	if (kcontrol->private_value & AUREON_AC97_STEREO)
		nvol |= ((0x1F - ucontrol->value.integer.value[1]) << 8) & 0x1F00;
	nvol |= ovol & ~0x1F1F;

	change = (ovol != nvol);
	if (change)
		aureon_ac97_write(ice, kcontrol->private_value & 0x7F, nvol);

	snd_ice1712_restore_gpio_status(ice);

	return change;
}