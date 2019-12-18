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
struct tun_struct {int owner; int group; } ;
struct net_device {int /*<<< orphan*/  destructor; int /*<<< orphan*/ * ethtool_ops; } ;

/* Variables and functions */
 struct tun_struct* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tun_ethtool_ops ; 
 int /*<<< orphan*/  tun_free_netdev ; 

__attribute__((used)) static void tun_setup(struct net_device *dev)
{
	struct tun_struct *tun = netdev_priv(dev);

	tun->owner = -1;
	tun->group = -1;

	dev->ethtool_ops = &tun_ethtool_ops;
	dev->destructor = tun_free_netdev;
}