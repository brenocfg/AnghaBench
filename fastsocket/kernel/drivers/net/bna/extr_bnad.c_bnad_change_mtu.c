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
struct bnad {int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int BNAD_JUMBO_MTU ; 
 int EBUSY ; 
 int EINVAL ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int ETH_ZLEN ; 
 int VLAN_HLEN ; 
 int bnad_mtu_set (struct bnad*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnad* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
bnad_change_mtu(struct net_device *netdev, int new_mtu)
{
	int err, mtu = netdev->mtu;
	struct bnad *bnad = netdev_priv(netdev);

	if (new_mtu + ETH_HLEN < ETH_ZLEN || new_mtu > BNAD_JUMBO_MTU)
		return -EINVAL;

	mutex_lock(&bnad->conf_mutex);

	netdev->mtu = new_mtu;

	mtu = ETH_HLEN + VLAN_HLEN + new_mtu + ETH_FCS_LEN;
	err = bnad_mtu_set(bnad, mtu);
	if (err)
		err = -EBUSY;

	mutex_unlock(&bnad->conf_mutex);
	return err;
}