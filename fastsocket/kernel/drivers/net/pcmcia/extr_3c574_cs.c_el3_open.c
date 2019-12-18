#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {int /*<<< orphan*/  open; } ;
struct net_device {scalar_t__ base_addr; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/ * function; } ;
struct el3_private {TYPE_1__ media; struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EL3_STATUS ; 
 int ENODEV ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  media_check ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 
 int /*<<< orphan*/  tc574_reset (struct net_device*) ; 

__attribute__((used)) static int el3_open(struct net_device *dev)
{
	struct el3_private *lp = netdev_priv(dev);
	struct pcmcia_device *link = lp->p_dev;

	if (!pcmcia_dev_present(link))
		return -ENODEV;
	
	link->open++;
	netif_start_queue(dev);
	
	tc574_reset(dev);
	lp->media.function = &media_check;
	lp->media.data = (unsigned long) dev;
	lp->media.expires = jiffies + HZ;
	add_timer(&lp->media);
	
	DEBUG(2, "%s: opened, status %4.4x.\n",
		  dev->name, inw(dev->base_addr + EL3_STATUS));
	
	return 0;
}