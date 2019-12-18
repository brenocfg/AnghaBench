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
struct fec_enet_private {scalar_t__ opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  fec_enet_free_buffers (struct net_device*) ; 
 int /*<<< orphan*/  fec_stop (struct net_device*) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int
fec_enet_close(struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);

	/* Don't know what to do yet. */
	fep->opened = 0;
	netif_stop_queue(dev);
	fec_stop(dev);

        fec_enet_free_buffers(dev);

	return 0;
}