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
typedef  size_t u16 ;
struct net_device {int dummy; } ;
struct be_adapter {int* vlan_tag; scalar_t__ vlans_added; } ;

/* Variables and functions */
 scalar_t__ be_max_vlans (struct be_adapter*) ; 
 int /*<<< orphan*/  be_physfn (struct be_adapter*) ; 
 int be_vid_config (struct be_adapter*) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void be_vlan_add_vid(struct net_device *netdev, u16 vid)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	int status = 0;

	if (!lancer_chip(adapter) && !be_physfn(adapter))
		return;

	/* Packets with VID 0 are always received by Lancer by default */
	if (lancer_chip(adapter) && vid == 0)
		return;

	adapter->vlan_tag[vid] = 1;
	if (adapter->vlans_added <= (be_max_vlans(adapter) + 1))
		status = be_vid_config(adapter);

	if (!status)
		adapter->vlans_added++;
	else
		adapter->vlan_tag[vid] = 0;
}