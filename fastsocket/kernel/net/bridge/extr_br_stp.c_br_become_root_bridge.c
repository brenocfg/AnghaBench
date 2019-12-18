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
struct net_bridge {scalar_t__ hello_time; int /*<<< orphan*/  hello_timer; TYPE_1__* dev; int /*<<< orphan*/  tcn_timer; int /*<<< orphan*/  bridge_forward_delay; int /*<<< orphan*/  forward_delay; scalar_t__ bridge_hello_time; int /*<<< orphan*/  bridge_max_age; int /*<<< orphan*/  max_age; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  br_config_bpdu_generation (struct net_bridge*) ; 
 int /*<<< orphan*/  br_topology_change_detection (struct net_bridge*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

void br_become_root_bridge(struct net_bridge *br)
{
	br->max_age = br->bridge_max_age;
	br->hello_time = br->bridge_hello_time;
	br->forward_delay = br->bridge_forward_delay;
	br_topology_change_detection(br);
	del_timer(&br->tcn_timer);

	if (br->dev->flags & IFF_UP) {
		br_config_bpdu_generation(br);
		mod_timer(&br->hello_timer, jiffies + br->hello_time);
	}
}