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
struct vlan_group {int dummy; } ;
struct qeth_card {struct vlan_group* vlangrp; } ;
struct net_device {int flags; } ;
struct in_device {int /*<<< orphan*/  mc_list_lock; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  IPA_FULL_VLAN ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int VLAN_GROUP_ARRAY_LEN ; 
 struct in_device* in_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in_dev_put (struct in_device*) ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_add_mc (struct qeth_card*,struct in_device*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct net_device* vlan_group_get_device (struct vlan_group*,int) ; 

__attribute__((used)) static void qeth_l3_add_vlan_mc(struct qeth_card *card)
{
	struct in_device *in_dev;
	struct vlan_group *vg;
	int i;

	QETH_DBF_TEXT(TRACE, 4, "addmcvl");
	if (!qeth_is_supported(card, IPA_FULL_VLAN) || (card->vlangrp == NULL))
		return;

	vg = card->vlangrp;
	for (i = 0; i < VLAN_GROUP_ARRAY_LEN; i++) {
		struct net_device *netdev = vlan_group_get_device(vg, i);
		if (netdev == NULL ||
		    !(netdev->flags & IFF_UP))
			continue;
		in_dev = in_dev_get(netdev);
		if (!in_dev)
			continue;
		read_lock(&in_dev->mc_list_lock);
		qeth_l3_add_mc(card, in_dev);
		read_unlock(&in_dev->mc_list_lock);
		in_dev_put(in_dev);
	}
}