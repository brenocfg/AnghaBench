#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct octeon_ethernet {scalar_t__ link_info; int queue; int /*<<< orphan*/  port; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {scalar_t__ full_duplex; int /*<<< orphan*/  speed; scalar_t__ link_up; } ;
struct TYPE_6__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_helper_link_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGPRINT (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_2__ cvmx_helper_link_autoconf (int /*<<< orphan*/ ) ; 
 TYPE_2__ cvmx_helper_link_get (int /*<<< orphan*/ ) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

__attribute__((used)) static void cvm_oct_xaui_poll(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	cvmx_helper_link_info_t link_info;

	link_info = cvmx_helper_link_get(priv->port);
	if (link_info.u64 == priv->link_info)
		return;

	link_info = cvmx_helper_link_autoconf(priv->port);
	priv->link_info = link_info.u64;

	/* Tell Linux */
	if (link_info.s.link_up) {

		if (!netif_carrier_ok(dev))
			netif_carrier_on(dev);
		if (priv->queue != -1)
			DEBUGPRINT
			    ("%s: %u Mbps %s duplex, port %2d, queue %2d\n",
			     dev->name, link_info.s.speed,
			     (link_info.s.full_duplex) ? "Full" : "Half",
			     priv->port, priv->queue);
		else
			DEBUGPRINT("%s: %u Mbps %s duplex, port %2d, POW\n",
				   dev->name, link_info.s.speed,
				   (link_info.s.full_duplex) ? "Full" : "Half",
				   priv->port);
	} else {
		if (netif_carrier_ok(dev))
			netif_carrier_off(dev);
		DEBUGPRINT("%s: Link down\n", dev->name);
	}
}