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
struct net_device {struct macvlan_port* macvlan_port; } ;
struct macvlan_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct macvlan_port*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct macvlan_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void macvlan_port_destroy(struct net_device *dev)
{
	struct macvlan_port *port = dev->macvlan_port;

	rcu_assign_pointer(dev->macvlan_port, NULL);
	synchronize_rcu();
	kfree(port);
}