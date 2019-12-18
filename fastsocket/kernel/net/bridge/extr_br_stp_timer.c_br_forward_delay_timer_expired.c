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
struct net_bridge_port {scalar_t__ state; int /*<<< orphan*/  forward_delay_timer; TYPE_2__* dev; int /*<<< orphan*/  port_no; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  lock; scalar_t__ forward_delay; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BR_STATE_FORWARDING ; 
 scalar_t__ BR_STATE_LEARNING ; 
 scalar_t__ BR_STATE_LISTENING ; 
 scalar_t__ br_is_designated_for_some_port (struct net_bridge*) ; 
 int /*<<< orphan*/  br_log_state (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_topology_change_detection (struct net_bridge*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_forward_delay_timer_expired(unsigned long arg)
{
	struct net_bridge_port *p = (struct net_bridge_port *) arg;
	struct net_bridge *br = p->br;

	pr_debug("%s: %d(%s) forward delay timer\n",
		 br->dev->name, p->port_no, p->dev->name);
	spin_lock(&br->lock);
	if (p->state == BR_STATE_LISTENING) {
		p->state = BR_STATE_LEARNING;
		mod_timer(&p->forward_delay_timer,
			  jiffies + br->forward_delay);
	} else if (p->state == BR_STATE_LEARNING) {
		p->state = BR_STATE_FORWARDING;
		if (br_is_designated_for_some_port(br))
			br_topology_change_detection(br);
	}
	br_log_state(p);
	spin_unlock(&br->lock);
}