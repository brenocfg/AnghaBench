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
typedef  size_t u16 ;
struct be_adapter {scalar_t__ vlans_added; int /*<<< orphan*/  if_handle; TYPE_1__* pdev; scalar_t__* vlan_tag; scalar_t__ promiscuous; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BE_NUM_VLANS_SUPPORTED ; 
 size_t VLAN_GROUP_ARRAY_LEN ; 
 int be_cmd_vlan_config (struct be_adapter*,int /*<<< orphan*/ ,size_t*,size_t,int,int) ; 
 scalar_t__ be_max_vlans (struct be_adapter*) ; 
 size_t cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int be_vid_config(struct be_adapter *adapter)
{
	u16 vids[BE_NUM_VLANS_SUPPORTED];
	u16 num = 0, i;
	int status = 0;

	/* No need to further configure vids if in promiscuous mode */
	if (adapter->promiscuous)
		return 0;

	if (adapter->vlans_added > be_max_vlans(adapter))
		goto set_vlan_promisc;

	/* Construct VLAN Table to give to HW */
	for (i = 0; i < VLAN_GROUP_ARRAY_LEN; i++)
		if (adapter->vlan_tag[i])
			vids[num++] = cpu_to_le16(i);

	status = be_cmd_vlan_config(adapter, adapter->if_handle,
				    vids, num, 1, 0);

	/* Set to VLAN promisc mode as setting VLAN filter failed */
	if (status) {
		dev_info(&adapter->pdev->dev, "Exhausted VLAN HW filters.\n");
		dev_info(&adapter->pdev->dev, "Disabling HW VLAN filtering.\n");
		goto set_vlan_promisc;
	}

	return status;

set_vlan_promisc:
	status = be_cmd_vlan_config(adapter, adapter->if_handle,
				    NULL, 0, 1, 1);
	return status;
}