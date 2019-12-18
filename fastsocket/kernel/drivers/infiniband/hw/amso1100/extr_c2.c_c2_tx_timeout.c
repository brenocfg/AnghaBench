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
struct net_device {int /*<<< orphan*/  name; } ;
struct c2_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  c2_tx_clean (struct c2_port*) ; 
 struct c2_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_timer (struct c2_port*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c2_tx_timeout(struct net_device *netdev)
{
	struct c2_port *c2_port = netdev_priv(netdev);

	if (netif_msg_timer(c2_port))
		pr_debug("%s: tx timeout\n", netdev->name);

	c2_tx_clean(c2_port);
}