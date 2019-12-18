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
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr {scalar_t__ sa_data; } ;
struct ql_adapter {int func; int /*<<< orphan*/  ndev; scalar_t__ current_mac_addr; } ;
struct net_device {scalar_t__ dev_addr; int /*<<< orphan*/  addr_len; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  MAC_ADDR_TYPE_CAM_MAC ; 
 int MAX_CQ ; 
 int /*<<< orphan*/  SEM_MAC_ADDR_MASK ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  is_valid_ether_addr (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_sem_spinlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_set_mac_addr_reg (struct ql_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qlge_set_mac_address(struct net_device *ndev, void *p)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	struct sockaddr *addr = p;
	int status;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;
	memcpy(ndev->dev_addr, addr->sa_data, ndev->addr_len);
	/* Update local copy of current mac address. */
	memcpy(qdev->current_mac_addr, ndev->dev_addr, ndev->addr_len);

	status = ql_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
	if (status)
		return status;
	status = ql_set_mac_addr_reg(qdev, (u8 *) ndev->dev_addr,
			MAC_ADDR_TYPE_CAM_MAC, qdev->func * MAX_CQ);
	if (status)
		netif_err(qdev, hw, qdev->ndev, "Failed to load MAC address.\n");
	ql_sem_unlock(qdev, SEM_MAC_ADDR_MASK);
	return status;
}