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
struct macvtap_queue {int /*<<< orphan*/  vlan; } ;
struct macvlan_dev {unsigned long tap_features; TYPE_1__* dev; } ;
struct TYPE_2__ {unsigned long features; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOLINK ; 
 unsigned long NETIF_F_HW_CSUM ; 
 unsigned long NETIF_F_TSO ; 
 unsigned long NETIF_F_TSO6 ; 
 unsigned long NETIF_F_TSO_ECN ; 
 unsigned long NETIF_F_UFO ; 
 unsigned long RX_OFFLOADS ; 
 unsigned long TUN_F_CSUM ; 
 unsigned long TUN_F_TSO4 ; 
 unsigned long TUN_F_TSO6 ; 
 unsigned long TUN_F_TSO_ECN ; 
 unsigned long TUN_F_UFO ; 
 int /*<<< orphan*/  netdev_features_change (TYPE_1__*) ; 
 unsigned long netdev_fix_features (unsigned long,int /*<<< orphan*/ ) ; 
 struct macvlan_dev* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_offload(struct macvtap_queue *q, unsigned long arg)
{
	struct macvlan_dev *vlan;
	unsigned long features;
	unsigned long tap_features = 0;

	vlan = rtnl_dereference(q->vlan);
	if (!vlan)
		return -ENOLINK;

	features = vlan->dev->features;

	if (arg & TUN_F_CSUM) {
		tap_features |= NETIF_F_HW_CSUM;

		if (arg & (TUN_F_TSO4 | TUN_F_TSO6)) {
			if (arg & TUN_F_TSO_ECN)
				tap_features |= NETIF_F_TSO_ECN;
			if (arg & TUN_F_TSO4)
				tap_features |= NETIF_F_TSO;
			if (arg & TUN_F_TSO6)
				tap_features |= NETIF_F_TSO6;
		}

		if (arg & TUN_F_UFO)
			tap_features |= NETIF_F_UFO;
	}

	/* tun/tap driver inverts the usage for TSO offloads, where
	 * setting the TSO bit means that the userspace wants to
	 * accept TSO frames and turning it off means that user space
	 * does not support TSO.
	 * For macvtap, we have to invert it to mean the same thing.
	 * When user space turns off TSO, we turn off GSO/LRO so that
	 * user-space will not receive TSO frames.
	 */
	if (tap_features & (NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_UFO))
		features |= RX_OFFLOADS;
	else
		features &= ~RX_OFFLOADS;

	/* tap_features are the same as features on tun/tap and
	 * reflect user expectations.
	 */
	features = netdev_fix_features(features, vlan->dev->name);
	vlan->tap_features = tap_features;
	if (vlan->dev->features != features) {
		vlan->dev->features = features;
		netdev_features_change(vlan->dev);
	}

	return 0;
}