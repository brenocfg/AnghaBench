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
struct net_device {unsigned int base_addr; } ;
struct TYPE_3__ {struct pcmcia_device* p_dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct net_device*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  PutByte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SelectPage (int) ; 
 int /*<<< orphan*/  XIRCREG1_IMR0 ; 
 int /*<<< orphan*/  XIRCREG4_GPR1 ; 
 int /*<<< orphan*/  XIRCREG_CR ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int
do_stop(struct net_device *dev)
{
    unsigned int ioaddr = dev->base_addr;
    local_info_t *lp = netdev_priv(dev);
    struct pcmcia_device *link = lp->p_dev;

    DEBUG(0, "do_stop(%p)\n", dev);

    if (!link)
	return -ENODEV;

    netif_stop_queue(dev);

    SelectPage(0);
    PutByte(XIRCREG_CR, 0);  /* disable interrupts */
    SelectPage(0x01);
    PutByte(XIRCREG1_IMR0, 0x00); /* forbid all ints */
    SelectPage(4);
    PutByte(XIRCREG4_GPR1, 0);	/* clear bit 0: power down */
    SelectPage(0);

    link->open--;
    return 0;
}