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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  addr_assign_type; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int EINVAL ; 
 scalar_t__ IS_MF_FCOE_AFEX (struct bnx2x*) ; 
 scalar_t__ IS_MF_STORAGE_SD (struct bnx2x*) ; 
 int /*<<< orphan*/  NET_ADDR_RANDOM ; 
 int /*<<< orphan*/  bnx2x_is_valid_ether_addr (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int bnx2x_set_eth_mac (struct bnx2x*,int) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

int bnx2x_change_mac_addr(struct net_device *dev, void *p)
{
	struct sockaddr *addr = p;
	struct bnx2x *bp = netdev_priv(dev);
	int rc = 0;

	if (!bnx2x_is_valid_ether_addr(bp, addr->sa_data)) {
		BNX2X_ERR("Requested MAC address is not valid\n");
		return -EINVAL;
	}

	if ((IS_MF_STORAGE_SD(bp) || IS_MF_FCOE_AFEX(bp)) &&
	    !is_zero_ether_addr(addr->sa_data)) {
		BNX2X_ERR("Can't configure non-zero address on iSCSI or FCoE functions in MF-SD mode\n");
		return -EINVAL;
	}

	if (netif_running(dev))  {
		rc = bnx2x_set_eth_mac(bp, false);
		if (rc)
			return rc;
	}

	dev->addr_assign_type &= ~NET_ADDR_RANDOM;
	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);

	if (netif_running(dev))
		rc = bnx2x_set_eth_mac(bp, true);

	return rc;
}