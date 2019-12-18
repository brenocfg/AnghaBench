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
struct net_device {int mtu; } ;
struct ipg_nic_private {int max_rxframe_size; int rxfrag_size; int rxsupport_size; int is_jumbo; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPG_DEBUG_MSG (char*) ; 
 int ipg_nic_open (struct net_device*) ; 
 int ipg_nic_stop (struct net_device*) ; 
 struct ipg_nic_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ipg_nic_change_mtu(struct net_device *dev, int new_mtu)
{
	struct ipg_nic_private *sp = netdev_priv(dev);
	int err;

	/* Function to accomodate changes to Maximum Transfer Unit
	 * (or MTU) of IPG NIC. Cannot use default function since
	 * the default will not allow for MTU > 1500 bytes.
	 */

	IPG_DEBUG_MSG("_nic_change_mtu\n");

	/*
	 * Check that the new MTU value is between 68 (14 byte header, 46 byte
	 * payload, 4 byte FCS) and 10 KB, which is the largest supported MTU.
	 */
	if (new_mtu < 68 || new_mtu > 10240)
		return -EINVAL;

	err = ipg_nic_stop(dev);
	if (err)
		return err;

	dev->mtu = new_mtu;

	sp->max_rxframe_size = new_mtu;

	sp->rxfrag_size = new_mtu;
	if (sp->rxfrag_size > 4088)
		sp->rxfrag_size = 4088;

	sp->rxsupport_size = sp->max_rxframe_size;

	if (new_mtu > 0x0600)
		sp->is_jumbo = true;
	else
		sp->is_jumbo = false;

	return ipg_nic_open(dev);
}