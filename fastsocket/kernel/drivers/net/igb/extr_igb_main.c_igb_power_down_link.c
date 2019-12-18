#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ media_type; } ;
struct TYPE_5__ {TYPE_1__ phy; } ;
struct igb_adapter {TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  igb_power_down_phy_copper_82575 (TYPE_2__*) ; 
 int /*<<< orphan*/  igb_shutdown_serdes_link_82575 (TYPE_2__*) ; 

__attribute__((used)) static void igb_power_down_link(struct igb_adapter *adapter)
{
	if (adapter->hw.phy.media_type == e1000_media_type_copper)
		igb_power_down_phy_copper_82575(&adapter->hw);
	else
		igb_shutdown_serdes_link_82575(&adapter->hw);
}