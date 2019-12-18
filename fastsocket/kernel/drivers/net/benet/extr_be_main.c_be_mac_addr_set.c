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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct sockaddr {scalar_t__ sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct device {int dummy; } ;
struct be_adapter {scalar_t__* pmac_id; int /*<<< orphan*/  if_handle; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EPERM ; 
 int ETH_ALEN ; 
 int be_cmd_get_active_mac (struct be_adapter*,scalar_t__,int /*<<< orphan*/ *) ; 
 int be_cmd_pmac_add (struct be_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_cmd_pmac_del (struct be_adapter*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  is_valid_ether_addr (scalar_t__) ; 
 scalar_t__ memcmp (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_mac_addr_set(struct net_device *netdev, void *p)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	struct device *dev = &adapter->pdev->dev;
	struct sockaddr *addr = p;
	int status;
	u8 mac[ETH_ALEN];
	u32 old_pmac_id = adapter->pmac_id[0], curr_pmac_id = 0;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	/* The PMAC_ADD cmd may fail if the VF doesn't have FILTMGMT
	 * privilege or if PF did not provision the new MAC address.
	 * On BE3, this cmd will always fail if the VF doesn't have the
	 * FILTMGMT privilege. This failure is OK, only if the PF programmed
	 * the MAC for the VF.
	 */
	status = be_cmd_pmac_add(adapter, (u8 *)addr->sa_data,
				 adapter->if_handle, &adapter->pmac_id[0], 0);
	if (!status) {
		curr_pmac_id = adapter->pmac_id[0];

		/* Delete the old programmed MAC. This call may fail if the
		 * old MAC was already deleted by the PF driver.
		 */
		if (adapter->pmac_id[0] != old_pmac_id)
			be_cmd_pmac_del(adapter, adapter->if_handle,
					old_pmac_id, 0);
	}

	/* Decide if the new MAC is successfully activated only after
	 * querying the FW
	 */
	status = be_cmd_get_active_mac(adapter, curr_pmac_id, mac);
	if (status)
		goto err;

	/* The MAC change did not happen, either due to lack of privilege
	 * or PF didn't pre-provision.
	 */
	if (memcmp(addr->sa_data, mac, ETH_ALEN)) {
		status = -EPERM;
		goto err;
	}

	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	dev_info(dev, "MAC address changed to %pM\n", mac);
	return 0;
err:
	dev_warn(dev, "MAC address change to %pM failed\n", addr->sa_data);
	return status;
}