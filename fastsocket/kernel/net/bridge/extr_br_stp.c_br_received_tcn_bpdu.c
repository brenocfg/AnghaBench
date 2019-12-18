#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_bridge_port {TYPE_3__* br; TYPE_2__* dev; int /*<<< orphan*/  port_no; } ;
struct TYPE_6__ {TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ br_is_designated_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_topology_change_acknowledge (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_topology_change_detection (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void br_received_tcn_bpdu(struct net_bridge_port *p)
{
	if (br_is_designated_port(p)) {
		pr_info("%s: received tcn bpdu on port %i(%s)\n",
		       p->br->dev->name, p->port_no, p->dev->name);

		br_topology_change_detection(p->br);
		br_topology_change_acknowledge(p);
	}
}