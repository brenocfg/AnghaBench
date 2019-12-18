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
struct net_bridge_port {scalar_t__ state; int /*<<< orphan*/  forward_delay_timer; struct net_bridge* br; } ;
struct net_bridge {scalar_t__ stp_enabled; scalar_t__ forward_delay; } ;

/* Variables and functions */
 scalar_t__ BR_KERNEL_STP ; 
 scalar_t__ BR_NO_STP ; 
 scalar_t__ BR_STATE_BLOCKING ; 
 scalar_t__ BR_STATE_FORWARDING ; 
 scalar_t__ BR_STATE_LEARNING ; 
 scalar_t__ BR_STATE_LISTENING ; 
 int /*<<< orphan*/  br_log_state (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_multicast_enable_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_topology_change_detection (struct net_bridge*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void br_make_forwarding(struct net_bridge_port *p)
{
	struct net_bridge *br = p->br;

	if (p->state != BR_STATE_BLOCKING)
		return;

	if (br->stp_enabled == BR_NO_STP || br->forward_delay == 0) {
		p->state = BR_STATE_FORWARDING;
		br_topology_change_detection(br);
		del_timer(&p->forward_delay_timer);
	}
	else if (br->stp_enabled == BR_KERNEL_STP)
		p->state = BR_STATE_LISTENING;
	else
		p->state = BR_STATE_LEARNING;

	br_multicast_enable_port(p);

	br_log_state(p);

	if (br->forward_delay != 0)
		mod_timer(&p->forward_delay_timer, jiffies + br->forward_delay);
}