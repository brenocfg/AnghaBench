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
typedef  scalar_t__ u32 ;
struct net_device {int mtu; int features; } ;
struct jme_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_TSO ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_set_tso(struct net_device *netdev, u32 on)
{
	struct jme_adapter *jme = netdev_priv(netdev);

	if (on) {
		set_bit(JME_FLAG_TSO, &jme->flags);
		if (netdev->mtu <= 1900)
			netdev->features |= NETIF_F_TSO | NETIF_F_TSO6;
	} else {
		clear_bit(JME_FLAG_TSO, &jme->flags);
		netdev->features &= ~(NETIF_F_TSO | NETIF_F_TSO6);
	}

	return 0;
}