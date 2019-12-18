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
struct be_async_event_grp5_cos_priority {int reco_default_priority; int /*<<< orphan*/  available_priority_bmap; scalar_t__ valid; } ;
struct be_adapter {int recommended_prio; int /*<<< orphan*/  vlan_prio_bmap; } ;

/* Variables and functions */
 int VLAN_PRIO_MASK ; 
 int VLAN_PRIO_SHIFT ; 

__attribute__((used)) static void be_async_grp5_cos_priority_process(struct be_adapter *adapter,
		struct be_async_event_grp5_cos_priority *evt)
{
	if (evt->valid) {
		adapter->vlan_prio_bmap = evt->available_priority_bmap;
		adapter->recommended_prio &= ~VLAN_PRIO_MASK;
		adapter->recommended_prio =
			evt->reco_default_priority << VLAN_PRIO_SHIFT;
	}
}