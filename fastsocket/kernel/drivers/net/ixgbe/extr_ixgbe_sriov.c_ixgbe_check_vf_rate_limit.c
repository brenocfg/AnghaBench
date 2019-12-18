#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ixgbe_adapter {scalar_t__ vf_rate_link_speed; int num_vfs; TYPE_1__* vfinfo; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ tx_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ixgbe_link_mbps (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_set_vf_rate_limit (struct ixgbe_adapter*,int) ; 

void ixgbe_check_vf_rate_limit(struct ixgbe_adapter *adapter)
{
	int i;

	/* VF Tx rate limit was not set */
	if (!adapter->vf_rate_link_speed)
		return;

	if (ixgbe_link_mbps(adapter) != adapter->vf_rate_link_speed) {
		adapter->vf_rate_link_speed = 0;
		dev_info(&adapter->pdev->dev,
			 "Link speed has been changed. VF Transmit rate is disabled\n");
	}

	for (i = 0; i < adapter->num_vfs; i++) {
		if (!adapter->vf_rate_link_speed)
			adapter->vfinfo[i].tx_rate = 0;

		ixgbe_set_vf_rate_limit(adapter, i);
	}
}