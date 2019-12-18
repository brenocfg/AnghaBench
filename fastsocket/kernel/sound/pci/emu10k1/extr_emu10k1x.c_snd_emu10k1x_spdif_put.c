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
struct TYPE_3__ {int* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;
struct emu10k1x {unsigned int* spdif_bits; } ;

/* Variables and functions */
 scalar_t__ SPCS0 ; 
 unsigned int snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_emu10k1x_ptr_write (struct emu10k1x*,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 struct emu10k1x* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_emu10k1x_spdif_put(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct emu10k1x *emu = snd_kcontrol_chip(kcontrol);
	unsigned int idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	int change;
	unsigned int val;

	val = (ucontrol->value.iec958.status[0] << 0) |
		(ucontrol->value.iec958.status[1] << 8) |
		(ucontrol->value.iec958.status[2] << 16) |
		(ucontrol->value.iec958.status[3] << 24);
	change = val != emu->spdif_bits[idx];
	if (change) {
		snd_emu10k1x_ptr_write(emu, SPCS0 + idx, 0, val);
		emu->spdif_bits[idx] = val;
	}
	return change;
}