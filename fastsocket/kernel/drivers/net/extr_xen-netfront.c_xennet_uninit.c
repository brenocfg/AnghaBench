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
struct netfront_info {int /*<<< orphan*/  gref_rx_head; int /*<<< orphan*/  gref_tx_head; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gnttab_free_grant_references (int /*<<< orphan*/ ) ; 
 struct netfront_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  xennet_release_rx_bufs (struct netfront_info*) ; 
 int /*<<< orphan*/  xennet_release_tx_bufs (struct netfront_info*) ; 

__attribute__((used)) static void xennet_uninit(struct net_device *dev)
{
	struct netfront_info *np = netdev_priv(dev);
	xennet_release_tx_bufs(np);
	xennet_release_rx_bufs(np);
	gnttab_free_grant_references(np->gref_tx_head);
	gnttab_free_grant_references(np->gref_rx_head);
}