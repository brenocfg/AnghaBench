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
struct snd_kcontrol {scalar_t__ private_value; } ;
struct snd_ice1712 {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int STAC946X_LF_VOLUME ; 
 int STAC946X_MASTER_VOLUME ; 
 int snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned char stac9460_2_get (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  stac9460_2_put (struct snd_ice1712*,int,int) ; 
 unsigned char stac9460_get (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  stac9460_put (struct snd_ice1712*,int,int) ; 

__attribute__((used)) static int stac9460_dac_vol_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	int idx, id;
	unsigned char tmp, ovol, nvol;
	int change;

	if (kcontrol->private_value) {
		idx = STAC946X_MASTER_VOLUME;
		nvol = ucontrol->value.integer.value[0] & 0x7f;
		tmp = stac9460_get(ice, idx);
		ovol = 0x7f - (tmp & 0x7f);
		change = (ovol != nvol);
		if (change) {
			stac9460_put(ice, idx, (0x7f - nvol) | (tmp & 0x80));
			stac9460_2_put(ice, idx, (0x7f - nvol) | (tmp & 0x80));
		}
	} else {
		id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
		idx = id + STAC946X_LF_VOLUME;
		nvol = ucontrol->value.integer.value[0] & 0x7f;
		if (id < 6)
			tmp = stac9460_get(ice, idx);
		else
			tmp = stac9460_2_get(ice, idx - 6);
		ovol = 0x7f - (tmp & 0x7f);
		change = (ovol != nvol);
		if (change) {
			if (id < 6)
				stac9460_put(ice, idx, (0x7f - nvol) |
							(tmp & 0x80));
			else
				stac9460_2_put(ice, idx-6, (0x7f - nvol) |
							(tmp & 0x80));
		}
	}
	return change;
}