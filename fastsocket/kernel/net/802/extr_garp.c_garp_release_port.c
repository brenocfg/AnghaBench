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
struct net_device {struct garp_port* garp_port; } ;
struct garp_port {scalar_t__* applicants; } ;

/* Variables and functions */
 unsigned int GARP_APPLICATION_MAX ; 
 int /*<<< orphan*/  kfree (struct garp_port*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct garp_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void garp_release_port(struct net_device *dev)
{
	struct garp_port *port = dev->garp_port;
	unsigned int i;

	for (i = 0; i <= GARP_APPLICATION_MAX; i++) {
		if (port->applicants[i])
			return;
	}
	rcu_assign_pointer(dev->garp_port, NULL);
	synchronize_rcu();
	kfree(port);
}