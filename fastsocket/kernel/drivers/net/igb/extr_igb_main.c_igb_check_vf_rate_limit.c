#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_8__ {TYPE_1__ mac; } ;
struct igb_adapter {int vf_rate_link_speed; int vfs_allocated_count; TYPE_3__* vf_data; TYPE_4__ hw; TYPE_2__* pdev; int /*<<< orphan*/  link_speed; } ;
struct TYPE_7__ {scalar_t__ tx_rate; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ e1000_82576 ; 
 int igb_link_mbps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_set_vf_rate_limit (TYPE_4__*,int,scalar_t__,int) ; 

__attribute__((used)) static void igb_check_vf_rate_limit(struct igb_adapter *adapter)
{
	int actual_link_speed, i;
	bool reset_rate = false;

	/* VF TX rate limit was not set or not supported */
	if ((adapter->vf_rate_link_speed == 0) ||
	    (adapter->hw.mac.type != e1000_82576))
		return;

	actual_link_speed = igb_link_mbps(adapter->link_speed);
	if (actual_link_speed != adapter->vf_rate_link_speed) {
		reset_rate = true;
		adapter->vf_rate_link_speed = 0;
		dev_info(&adapter->pdev->dev,
			 "Link speed has been changed. VF Transmit rate is disabled\n");
	}

	for (i = 0; i < adapter->vfs_allocated_count; i++) {
		if (reset_rate)
			adapter->vf_data[i].tx_rate = 0;

		igb_set_vf_rate_limit(&adapter->hw, i,
				      adapter->vf_data[i].tx_rate,
				      actual_link_speed);
	}
}