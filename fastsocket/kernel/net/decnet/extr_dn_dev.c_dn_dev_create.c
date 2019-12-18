#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {scalar_t__ type; struct dn_dev* dn_ptr; } ;
struct dn_dev_parms {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ (* up ) (struct net_device*) ;} ;
struct dn_dev {TYPE_1__ parms; int /*<<< orphan*/  neigh_parms; int /*<<< orphan*/  uptime; int /*<<< orphan*/  timer; struct net_device* dev; } ;

/* Variables and functions */
 int DN_DEV_LIST_SIZE ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct dn_dev_parms* dn_dev_list ; 
 int /*<<< orphan*/  dn_dev_set_timer (struct net_device*) ; 
 int /*<<< orphan*/  dn_dev_sysctl_register (struct net_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  dn_neigh_table ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct dn_dev*) ; 
 struct dn_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct dn_dev_parms*,int) ; 
 int /*<<< orphan*/  neigh_parms_alloc (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_parms_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ stub1 (struct net_device*) ; 

__attribute__((used)) static struct dn_dev *dn_dev_create(struct net_device *dev, int *err)
{
	int i;
	struct dn_dev_parms *p = dn_dev_list;
	struct dn_dev *dn_db;

	for(i = 0; i < DN_DEV_LIST_SIZE; i++, p++) {
		if (p->type == dev->type)
			break;
	}

	*err = -ENODEV;
	if (i == DN_DEV_LIST_SIZE)
		return NULL;

	*err = -ENOBUFS;
	if ((dn_db = kzalloc(sizeof(struct dn_dev), GFP_ATOMIC)) == NULL)
		return NULL;

	memcpy(&dn_db->parms, p, sizeof(struct dn_dev_parms));
	smp_wmb();
	dev->dn_ptr = dn_db;
	dn_db->dev = dev;
	init_timer(&dn_db->timer);

	dn_db->uptime = jiffies;

	dn_db->neigh_parms = neigh_parms_alloc(dev, &dn_neigh_table);
	if (!dn_db->neigh_parms) {
		dev->dn_ptr = NULL;
		kfree(dn_db);
		return NULL;
	}

	if (dn_db->parms.up) {
		if (dn_db->parms.up(dev) < 0) {
			neigh_parms_release(&dn_neigh_table, dn_db->neigh_parms);
			dev->dn_ptr = NULL;
			kfree(dn_db);
			return NULL;
		}
	}

	dn_dev_sysctl_register(dev, &dn_db->parms);

	dn_dev_set_timer(dev);

	*err = 0;
	return dn_db;
}