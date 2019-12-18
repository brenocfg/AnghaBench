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
struct pcmcia_device {int /*<<< orphan*/  open; } ;
struct net_device {unsigned int base_addr; int /*<<< orphan*/  name; } ;
struct local_info_t {scalar_t__ cardtype; scalar_t__ open_time; struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_OFF ; 
 int /*<<< orphan*/  CONFIG0_RST ; 
 int /*<<< orphan*/  CONFIG0_RST_1 ; 
 scalar_t__ CONFIG_0 ; 
 scalar_t__ CONFIG_1 ; 
 int /*<<< orphan*/  DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTR_OFF ; 
 scalar_t__ LAN_CTRL ; 
 scalar_t__ MBH10302 ; 
 struct local_info_t* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sram_config ; 

__attribute__((used)) static int fjn_close(struct net_device *dev)
{
    struct local_info_t *lp = netdev_priv(dev);
    struct pcmcia_device *link = lp->p_dev;
    unsigned int ioaddr = dev->base_addr;

    DEBUG(4, "fjn_close('%s').\n", dev->name);

    lp->open_time = 0;
    netif_stop_queue(dev);

    /* Set configuration register 0 to disable Tx and Rx. */
    if( sram_config == 0 ) 
	outb(CONFIG0_RST ,ioaddr + CONFIG_0);
    else
	outb(CONFIG0_RST_1 ,ioaddr + CONFIG_0);

    /* Update the statistics -- ToDo. */

    /* Power-down the chip.  Green, green, green! */
    outb(CHIP_OFF ,ioaddr + CONFIG_1);

    /* Set the ethernet adaptor disable IRQ */
    if (lp->cardtype == MBH10302)
	outb(INTR_OFF, ioaddr + LAN_CTRL);

    link->open--;

    return 0;
}