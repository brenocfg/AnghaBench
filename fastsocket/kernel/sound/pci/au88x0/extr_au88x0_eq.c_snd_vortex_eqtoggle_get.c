#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ this54; } ;
struct TYPE_8__ {TYPE_4__ eq; } ;
typedef  TYPE_3__ vortex_t ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_6__ {int* value; } ;
struct TYPE_7__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
typedef  TYPE_4__ eqlzr_t ;

/* Variables and functions */
 TYPE_3__* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int
snd_vortex_eqtoggle_get(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	eqlzr_t *eq = &(vortex->eq);
	//int i = kcontrol->private_value;

	ucontrol->value.integer.value[0] = eq->this54 ? 0 : 1;

	return 0;
}