#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {scalar_t__ win; struct net_device* priv; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ramBase; } ;
typedef  TYPE_1__ netwave_private ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void netwave_release(struct pcmcia_device *link)
{
	struct net_device *dev = link->priv;
	netwave_private *priv = netdev_priv(dev);

	DEBUG(0, "netwave_release(0x%p)\n", link);

	pcmcia_disable_device(link);
	if (link->win)
		iounmap(priv->ramBase);
}