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
struct pcmcia_device {int /*<<< orphan*/  open; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct pcmcia_device* p_dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct net_device*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  do_reset (struct net_device*,int) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 

__attribute__((used)) static int
do_open(struct net_device *dev)
{
    local_info_t *lp = netdev_priv(dev);
    struct pcmcia_device *link = lp->p_dev;

    DEBUG(0, "do_open(%p)\n", dev);

    /* Check that the PCMCIA card is still here. */
    /* Physical device present signature. */
    if (!pcmcia_dev_present(link))
	return -ENODEV;

    /* okay */
    link->open++;

    netif_start_queue(dev);
    do_reset(dev,1);

    return 0;
}