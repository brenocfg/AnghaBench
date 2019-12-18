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
struct snd_pt2258 {scalar_t__* volume; } ;
struct snd_kcontrol {int private_value; struct snd_pt2258* private_data; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */

__attribute__((used)) static int pt2258_stereo_volume_get(struct snd_kcontrol *kcontrol,
				    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pt2258 *pt = kcontrol->private_data;
	int base = kcontrol->private_value;

	/* chip does not support register reads */
	ucontrol->value.integer.value[0] = 79 - pt->volume[base];
	ucontrol->value.integer.value[1] = 79 - pt->volume[base + 1];
	return 0;
}