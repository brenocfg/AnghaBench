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
struct be_adapter {int /*<<< orphan*/ * pmac_id; int /*<<< orphan*/  if_handle; TYPE_1__* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/ * perm_addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int be_cmd_get_perm_mac (struct be_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_cmd_pmac_add (struct be_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int be_mac_setup(struct be_adapter *adapter)
{
	u8 mac[ETH_ALEN];
	int status;

	if (is_zero_ether_addr(adapter->netdev->dev_addr)) {
		status = be_cmd_get_perm_mac(adapter, mac);
		if (status)
			return status;

		memcpy(adapter->netdev->dev_addr, mac, ETH_ALEN);
		memcpy(adapter->netdev->perm_addr, mac, ETH_ALEN);
	} else {
		/* Maybe the HW was reset; dev_addr must be re-programmed */
		memcpy(mac, adapter->netdev->dev_addr, ETH_ALEN);
	}

	/* On BE3 VFs this cmd may fail due to lack of privilege.
	 * Ignore the failure as in this case pmac_id is fetched
	 * in the IFACE_CREATE cmd.
	 */
	be_cmd_pmac_add(adapter, mac, adapter->if_handle,
			&adapter->pmac_id[0], 0);
	return 0;
}