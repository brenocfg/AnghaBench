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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  QLCNIC_MAC_ADD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_sre_macaddr_change (struct qlcnic_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qlcnic_83xx_change_l2_filter(struct qlcnic_adapter *adapter, u64 *addr,
				  u16 vlan_id)
{
	u8 mac[ETH_ALEN];
	memcpy(&mac, addr, ETH_ALEN);
	qlcnic_83xx_sre_macaddr_change(adapter, mac, vlan_id, QLCNIC_MAC_ADD);
}