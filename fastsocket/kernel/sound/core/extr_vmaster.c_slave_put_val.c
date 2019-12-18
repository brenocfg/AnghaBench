#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* value; } ;
struct TYPE_10__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_4__ value; } ;
struct TYPE_11__ {int (* put ) (TYPE_5__*,struct snd_ctl_elem_value*) ;} ;
struct TYPE_8__ {int type; int count; int min_val; int max_val; } ;
struct link_slave {TYPE_5__ slave; TYPE_2__ info; TYPE_6__* master; } ;
struct TYPE_7__ {int max_val; } ;
struct TYPE_12__ {int val; TYPE_1__ info; } ;

/* Variables and functions */
#define  SNDRV_CTL_ELEM_TYPE_BOOLEAN 129 
#define  SNDRV_CTL_ELEM_TYPE_INTEGER 128 
 int master_init (TYPE_6__*) ; 
 int stub1 (TYPE_5__*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int slave_put_val(struct link_slave *slave,
			 struct snd_ctl_elem_value *ucontrol)
{
	int err, ch, vol;

	err = master_init(slave->master);
	if (err < 0)
		return err;

	switch (slave->info.type) {
	case SNDRV_CTL_ELEM_TYPE_BOOLEAN:
		for (ch = 0; ch < slave->info.count; ch++)
			ucontrol->value.integer.value[ch] &=
				!!slave->master->val;
		break;
	case SNDRV_CTL_ELEM_TYPE_INTEGER:
		for (ch = 0; ch < slave->info.count; ch++) {
			/* max master volume is supposed to be 0 dB */
			vol = ucontrol->value.integer.value[ch];
			vol += slave->master->val - slave->master->info.max_val;
			if (vol < slave->info.min_val)
				vol = slave->info.min_val;
			else if (vol > slave->info.max_val)
				vol = slave->info.max_val;
			ucontrol->value.integer.value[ch] = vol;
		}
		break;
	}
	return slave->slave.put(&slave->slave, ucontrol);
}