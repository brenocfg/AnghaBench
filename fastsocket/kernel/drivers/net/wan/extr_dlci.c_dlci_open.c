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
struct net_device {scalar_t__ dev_addr; } ;
struct frad_local {int (* activate ) (struct net_device*,struct net_device*) ;} ;
struct dlci_local {struct net_device* slave; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 void* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int stub1 (struct net_device*,struct net_device*) ; 

__attribute__((used)) static int dlci_open(struct net_device *dev)
{
	struct dlci_local	*dlp;
	struct frad_local	*flp;
	int			err;

	dlp = netdev_priv(dev);

	if (!*(short *)(dev->dev_addr))
		return(-EINVAL);

	if (!netif_running(dlp->slave))
		return(-ENOTCONN);

	flp = netdev_priv(dlp->slave);
	err = (*flp->activate)(dlp->slave, dev);
	if (err)
		return(err);

	netif_start_queue(dev);

	return 0;
}