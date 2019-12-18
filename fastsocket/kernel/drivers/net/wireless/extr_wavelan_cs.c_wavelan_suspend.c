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
struct pcmcia_device {scalar_t__ open; scalar_t__ priv; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int HACR_DEFAULT ; 
 int HACR_PWR_STAT ; 
 int /*<<< orphan*/  hacr_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  wv_ru_stop (struct net_device*) ; 

__attribute__((used)) static int wavelan_suspend(struct pcmcia_device *link)
{
	struct net_device *	dev = (struct net_device *) link->priv;

	/* NB: wavelan_close will be called, but too late, so we are
	 * obliged to close nicely the wavelan here. David, could you
	 * close the device before suspending them ? And, by the way,
	 * could you, on resume, add a "route add -net ..." after the
	 * ifconfig up ? Thanks... */

	/* Stop receiving new messages and wait end of transmission */
	wv_ru_stop(dev);

	if (link->open)
		netif_device_detach(dev);

	/* Power down the module */
	hacr_write(dev->base_addr, HACR_DEFAULT & (~HACR_PWR_STAT));

	return 0;
}