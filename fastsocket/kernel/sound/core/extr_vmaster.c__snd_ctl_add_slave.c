#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  c; } ;
struct snd_kcontrol {int count; int /*<<< orphan*/  private_free; struct link_slave* private_data; TYPE_1__ tlv; TYPE_2__* vd; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; } ;
struct link_slave {unsigned int flags; int /*<<< orphan*/  list; struct link_master* master; struct snd_kcontrol slave; struct snd_kcontrol* kctl; } ;
struct link_master {int /*<<< orphan*/  slaves; } ;
struct TYPE_5__ {int access; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK ; 
 struct link_slave* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  slave_free ; 
 int /*<<< orphan*/  slave_get ; 
 int /*<<< orphan*/  slave_info ; 
 int /*<<< orphan*/  slave_put ; 
 int /*<<< orphan*/  slave_tlv_cmd ; 
 struct link_master* snd_kcontrol_chip (struct snd_kcontrol*) ; 

int _snd_ctl_add_slave(struct snd_kcontrol *master, struct snd_kcontrol *slave,
		       unsigned int flags)
{
	struct link_master *master_link = snd_kcontrol_chip(master);
	struct link_slave *srec;

	srec = kzalloc(sizeof(*srec) +
		       slave->count * sizeof(*slave->vd), GFP_KERNEL);
	if (!srec)
		return -ENOMEM;
	srec->kctl = slave;
	srec->slave = *slave;
	memcpy(srec->slave.vd, slave->vd, slave->count * sizeof(*slave->vd));
	srec->master = master_link;
	srec->flags = flags;

	/* override callbacks */
	slave->info = slave_info;
	slave->get = slave_get;
	slave->put = slave_put;
	if (slave->vd[0].access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK)
		slave->tlv.c = slave_tlv_cmd;
	slave->private_data = srec;
	slave->private_free = slave_free;

	list_add_tail(&srec->list, &master_link->slaves);
	return 0;
}