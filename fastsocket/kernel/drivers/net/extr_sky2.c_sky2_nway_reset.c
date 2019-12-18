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
struct sky2_port {int flags; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SKY2_FLAG_AUTO_SPEED ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  sky2_phy_reinit (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_set_multicast (struct net_device*) ; 

__attribute__((used)) static int sky2_nway_reset(struct net_device *dev)
{
	struct sky2_port *sky2 = netdev_priv(dev);

	if (!netif_running(dev) || !(sky2->flags & SKY2_FLAG_AUTO_SPEED))
		return -EINVAL;

	sky2_phy_reinit(sky2);
	sky2_set_multicast(dev);

	return 0;
}