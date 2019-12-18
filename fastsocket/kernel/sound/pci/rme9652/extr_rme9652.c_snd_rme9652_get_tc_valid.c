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
struct snd_rme9652 {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  RME9652_status_register ; 
 int RME9652_tc_valid ; 
 int rme9652_read (struct snd_rme9652*,int /*<<< orphan*/ ) ; 
 struct snd_rme9652* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_rme9652_get_tc_valid(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	
	ucontrol->value.integer.value[0] = 
		(rme9652_read(rme9652, RME9652_status_register) & RME9652_tc_valid) ? 1 : 0;
	return 0;
}