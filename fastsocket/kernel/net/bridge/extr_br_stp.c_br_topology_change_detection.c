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
struct net_bridge {scalar_t__ stp_enabled; int topology_change; int topology_change_detected; scalar_t__ bridge_hello_time; int /*<<< orphan*/  tcn_timer; scalar_t__ bridge_max_age; scalar_t__ bridge_forward_delay; int /*<<< orphan*/  topology_change_timer; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BR_KERNEL_STP ; 
 int br_is_root_bridge (struct net_bridge*) ; 
 int /*<<< orphan*/  br_transmit_tcn (struct net_bridge*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 

void br_topology_change_detection(struct net_bridge *br)
{
	int isroot = br_is_root_bridge(br);

	if (br->stp_enabled != BR_KERNEL_STP)
		return;

	pr_info("%s: topology change detected, %s\n", br->dev->name,
		isroot ? "propagating" : "sending tcn bpdu");

	if (isroot) {
		br->topology_change = 1;
		mod_timer(&br->topology_change_timer, jiffies
			  + br->bridge_forward_delay + br->bridge_max_age);
	} else if (!br->topology_change_detected) {
		br_transmit_tcn(br);
		mod_timer(&br->tcn_timer, jiffies + br->bridge_hello_time);
	}

	br->topology_change_detected = 1;
}