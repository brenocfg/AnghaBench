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
struct pcmcia_device {scalar_t__ open; struct net_device* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL3501_RESUME ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  wl3501_pwr_mgmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl3501_reset (struct net_device*) ; 

__attribute__((used)) static int wl3501_resume(struct pcmcia_device *link)
{
	struct net_device *dev = link->priv;

	wl3501_pwr_mgmt(netdev_priv(dev), WL3501_RESUME);
	if (link->open) {
		wl3501_reset(dev);
		netif_device_attach(dev);
	}

	return 0;
}