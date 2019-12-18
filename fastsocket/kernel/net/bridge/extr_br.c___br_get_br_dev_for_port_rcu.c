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
struct net_device {int /*<<< orphan*/  br_port; } ;
struct net_bridge_port {TYPE_1__* br; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 struct net_bridge_port* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *__br_get_br_dev_for_port_rcu(struct net_device *port_dev)
{
	struct net_bridge_port *port = rcu_dereference(port_dev->br_port);
	return port ? port->br->dev : NULL;
}