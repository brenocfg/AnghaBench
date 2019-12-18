#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int addr_len; } ;
struct TYPE_6__ {TYPE_1__* ndev; } ;
typedef  TYPE_2__ islpci_private ;
struct TYPE_5__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GEN_OID_MACADDRESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mgt_set_request (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 

int
prism54_set_mac_address(struct net_device *ndev, void *addr)
{
	islpci_private *priv = netdev_priv(ndev);
	int ret;

	if (ndev->addr_len != 6)
		return -EINVAL;
	ret = mgt_set_request(priv, GEN_OID_MACADDRESS, 0,
			      &((struct sockaddr *) addr)->sa_data);
	if (!ret)
		memcpy(priv->ndev->dev_addr,
		       &((struct sockaddr *) addr)->sa_data, 6);

	return ret;
}