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
typedef  scalar_t__ u_long ;
struct TYPE_3__ {scalar_t__ expires; scalar_t__ data; int /*<<< orphan*/ * function; } ;
struct smc_private {TYPE_1__ media; scalar_t__ packets_waiting; int /*<<< orphan*/ * saved_skb; struct pcmcia_device* p_dev; } ;
struct pcmcia_device {int /*<<< orphan*/  open; } ;
struct net_device {scalar_t__ base_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BANK_SELECT ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ check_sig (struct pcmcia_device*) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  media_check ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int pc_debug ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  smc_dump (struct net_device*) ; 
 int /*<<< orphan*/  smc_reset (struct net_device*) ; 

__attribute__((used)) static int smc_open(struct net_device *dev)
{
    struct smc_private *smc = netdev_priv(dev);
    struct pcmcia_device *link = smc->p_dev;

#ifdef PCMCIA_DEBUG
    DEBUG(0, "%s: smc_open(%p), ID/Window %4.4x.\n",
	  dev->name, dev, inw(dev->base_addr + BANK_SELECT));
    if (pc_debug > 1) smc_dump(dev);
#endif

    /* Check that the PCMCIA card is still here. */
    if (!pcmcia_dev_present(link))
	return -ENODEV;
    /* Physical device present signature. */
    if (check_sig(link) < 0) {
	printk("smc91c92_cs: Yikes!  Bad chip signature!\n");
	return -ENODEV;
    }
    link->open++;

    netif_start_queue(dev);
    smc->saved_skb = NULL;
    smc->packets_waiting = 0;

    smc_reset(dev);
    init_timer(&smc->media);
    smc->media.function = &media_check;
    smc->media.data = (u_long) dev;
    smc->media.expires = jiffies + HZ;
    add_timer(&smc->media);

    return 0;
}