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
struct smc_private {int /*<<< orphan*/  base; } ;
struct pcmcia_device {struct net_device* priv; scalar_t__ win; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void smc91c92_release(struct pcmcia_device *link)
{
	DEBUG(0, "smc91c92_release(0x%p)\n", link);
	if (link->win) {
		struct net_device *dev = link->priv;
		struct smc_private *smc = netdev_priv(dev);
		iounmap(smc->base);
	}
	pcmcia_disable_device(link);
}