#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_info {int dummy; } ;
struct TYPE_2__ {int (* info ) (TYPE_1__*,struct snd_ctl_elem_info*) ;} ;
struct link_slave {TYPE_1__ slave; } ;

/* Variables and functions */
 struct link_slave* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int stub1 (TYPE_1__*,struct snd_ctl_elem_info*) ; 

__attribute__((used)) static int slave_info(struct snd_kcontrol *kcontrol,
		      struct snd_ctl_elem_info *uinfo)
{
	struct link_slave *slave = snd_kcontrol_chip(kcontrol);
	return slave->slave.info(&slave->slave, uinfo);
}