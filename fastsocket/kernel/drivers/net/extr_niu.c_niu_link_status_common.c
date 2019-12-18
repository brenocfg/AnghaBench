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
struct niu_link_config {scalar_t__ active_speed; scalar_t__ active_duplex; } ;
struct niu {int /*<<< orphan*/  lock; struct net_device* dev; struct niu_link_config link_config; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  LINK ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_10000 ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  niu_handle_led (struct niu*,int) ; 
 int /*<<< orphan*/  niu_init_xif (struct niu*) ; 
 int /*<<< orphan*/  niuinfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  niuwarn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int niu_link_status_common(struct niu *np, int link_up)
{
	struct niu_link_config *lp = &np->link_config;
	struct net_device *dev = np->dev;
	unsigned long flags;

	if (!netif_carrier_ok(dev) && link_up) {
		niuinfo(LINK, "%s: Link is up at %s, %s duplex\n",
		       dev->name,
		       (lp->active_speed == SPEED_10000 ?
			"10Gb/sec" :
			(lp->active_speed == SPEED_1000 ?
			 "1Gb/sec" :
			 (lp->active_speed == SPEED_100 ?
			  "100Mbit/sec" : "10Mbit/sec"))),
		       (lp->active_duplex == DUPLEX_FULL ?
			"full" : "half"));

		spin_lock_irqsave(&np->lock, flags);
		niu_init_xif(np);
		niu_handle_led(np, 1);
		spin_unlock_irqrestore(&np->lock, flags);

		netif_carrier_on(dev);
	} else if (netif_carrier_ok(dev) && !link_up) {
		niuwarn(LINK, "%s: Link is down\n", dev->name);
		spin_lock_irqsave(&np->lock, flags);
		niu_handle_led(np, 0);
		spin_unlock_irqrestore(&np->lock, flags);
		netif_carrier_off(dev);
	}

	return 0;
}