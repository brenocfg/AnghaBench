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
struct vx_vu_meter {int /*<<< orphan*/  saturated; } ;
struct vx_core {int dummy; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct vx_core* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  vx_get_audio_vu_meter (struct vx_core*,int,int,struct vx_vu_meter*) ; 

__attribute__((used)) static int vx_saturation_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct vx_core *chip = snd_kcontrol_chip(kcontrol);
	struct vx_vu_meter meter[2];
	int audio = kcontrol->private_value & 0xff;

	vx_get_audio_vu_meter(chip, audio, 1, meter); /* capture only */
	ucontrol->value.integer.value[0] = meter[0].saturated;
	ucontrol->value.integer.value[1] = meter[1].saturated;
	return 0;
}