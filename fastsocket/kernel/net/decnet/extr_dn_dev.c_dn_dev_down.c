#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {struct dn_dev* dn_ptr; } ;
struct dn_ifaddr {int dummy; } ;
struct dn_dev {struct dn_ifaddr* ifa_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dn_dev_del_ifa (struct dn_dev*,struct dn_ifaddr**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_dev_delete (struct net_device*) ; 
 int /*<<< orphan*/  dn_dev_free_ifa (struct dn_ifaddr*) ; 

void dn_dev_down(struct net_device *dev)
{
	struct dn_dev *dn_db = dev->dn_ptr;
	struct dn_ifaddr *ifa;

	if (dn_db == NULL)
		return;

	while((ifa = dn_db->ifa_list) != NULL) {
		dn_dev_del_ifa(dn_db, &dn_db->ifa_list, 0);
		dn_dev_free_ifa(ifa);
	}

	dn_dev_delete(dev);
}