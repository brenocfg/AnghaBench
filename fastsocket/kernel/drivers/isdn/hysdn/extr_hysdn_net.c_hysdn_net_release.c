#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_local {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int debug_flags; struct net_device* netif; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 int LOG_NET_INIT ; 
 int /*<<< orphan*/  flush_tx_buffers (struct net_local*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hysdn_addlog (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  net_close (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

int
hysdn_net_release(hysdn_card * card)
{
	struct net_device *dev = card->netif;

	if (!dev)
		return (0);	/* non existing */

	card->netif = NULL;	/* clear out pointer */
	net_close(dev);

	flush_tx_buffers((struct net_local *) dev);	/* empty buffers */

	unregister_netdev(dev);	/* release the device */
	free_netdev(dev);	/* release the memory allocated */
	if (card->debug_flags & LOG_NET_INIT)
		hysdn_addlog(card, "network device deleted");

	return (0);		/* always successful */
}