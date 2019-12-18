#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int private_value; } ;
struct TYPE_5__ {int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** mixer_volume; } ;
typedef  TYPE_3__ snd_card_saa7134_t ;

/* Variables and functions */
 TYPE_3__* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_saa7134_volume_get(struct snd_kcontrol * kcontrol,
				  struct snd_ctl_elem_value * ucontrol)
{
	snd_card_saa7134_t *chip = snd_kcontrol_chip(kcontrol);
	int addr = kcontrol->private_value;

	ucontrol->value.integer.value[0] = chip->mixer_volume[addr][0];
	ucontrol->value.integer.value[1] = chip->mixer_volume[addr][1];
	return 0;
}