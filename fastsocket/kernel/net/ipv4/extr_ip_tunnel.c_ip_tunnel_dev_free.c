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
struct net_device {int dummy; } ;
struct ip_tunnel {int /*<<< orphan*/  gro_cells; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  gro_cells_destroy (int /*<<< orphan*/ *) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ip_tunnel_dev_free(struct net_device *dev)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);

	gro_cells_destroy(&tunnel->gro_cells);
	free_netdev(dev);
}