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
struct net_bridge_port {scalar_t__ config_pending; scalar_t__ topology_change_ack; int /*<<< orphan*/  state; int /*<<< orphan*/  port_no; int /*<<< orphan*/  priority; int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_STATE_BLOCKING ; 
 int /*<<< orphan*/  br_become_designated_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_make_port_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void br_init_port(struct net_bridge_port *p)
{
	p->port_id = br_make_port_id(p->priority, p->port_no);
	br_become_designated_port(p);
	p->state = BR_STATE_BLOCKING;
	p->topology_change_ack = 0;
	p->config_pending = 0;
}