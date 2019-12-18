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
typedef  int /*<<< orphan*/  u32 ;
struct be_adapter {int /*<<< orphan*/  if_handle; } ;

/* Variables and functions */
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 int be_cmd_get_mac_from_list (struct be_adapter*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int be_cmd_mac_addr_query (struct be_adapter*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int be_cmd_get_active_mac(struct be_adapter *adapter, u32 curr_pmac_id, u8 *mac)
{
	bool active = true;

	if (BEx_chip(adapter))
		return be_cmd_mac_addr_query(adapter, mac, false,
					     adapter->if_handle, curr_pmac_id);
	else
		/* Fetch the MAC address using pmac_id */
		return be_cmd_get_mac_from_list(adapter, mac, &active,
						&curr_pmac_id, 0);
}