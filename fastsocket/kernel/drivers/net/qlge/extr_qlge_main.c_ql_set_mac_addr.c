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
struct ql_adapter {char* current_mac_addr; int func; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  MAC_ADDR_TYPE_CAM_MAC ; 
 int MAX_CQ ; 
 int /*<<< orphan*/  SEM_MAC_ADDR_MASK ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_printk (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int ql_sem_spinlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_set_mac_addr_reg (struct ql_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ql_set_mac_addr(struct ql_adapter *qdev, int set)
{
	int status;
	char zero_mac_addr[ETH_ALEN];
	char *addr;

	if (set) {
		addr = &qdev->current_mac_addr[0];
		netif_printk(qdev, ifup, KERN_DEBUG, qdev->ndev,
			     "Set Mac addr %pM\n", addr);
	} else {
		memset(zero_mac_addr, 0, ETH_ALEN);
		addr = &zero_mac_addr[0];
		netif_printk(qdev, ifup, KERN_DEBUG, qdev->ndev,
			     "Clearing MAC address\n");
	}
	status = ql_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
	if (status)
		return status;
	status = ql_set_mac_addr_reg(qdev, (u8 *) addr,
			MAC_ADDR_TYPE_CAM_MAC, qdev->func * MAX_CQ);
	ql_sem_unlock(qdev, SEM_MAC_ADDR_MASK);
	if (status)
		netif_err(qdev, ifup, qdev->ndev,
			  "Failed to init mac address.\n");
	return status;
}