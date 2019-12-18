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
typedef  scalar_t__ u_long ;
struct pcmcia_device {int /*<<< orphan*/  open; } ;
struct net_device {unsigned int base_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ expires; scalar_t__ data; int /*<<< orphan*/ * function; } ;
struct TYPE_5__ {int link_status; TYPE_2__ watchdog; struct pcmcia_device* p_dev; } ;
typedef  TYPE_1__ axnet_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ EN0_ISR ; 
 int ENODEV ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 TYPE_1__* PRIV (struct net_device*) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int ax_open (struct net_device*) ; 
 int /*<<< orphan*/  ei_irq_wrapper ; 
 int /*<<< orphan*/  ei_watchdog ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct net_device*) ; 

__attribute__((used)) static int axnet_open(struct net_device *dev)
{
    int ret;
    axnet_dev_t *info = PRIV(dev);
    struct pcmcia_device *link = info->p_dev;
    unsigned int nic_base = dev->base_addr;
    
    DEBUG(2, "axnet_open('%s')\n", dev->name);

    if (!pcmcia_dev_present(link))
	return -ENODEV;

    outb_p(0xFF, nic_base + EN0_ISR); /* Clear bogus intr. */
    ret = request_irq(dev->irq, ei_irq_wrapper, IRQF_SHARED, "axnet_cs", dev);
    if (ret)
	    return ret;

    link->open++;

    info->link_status = 0x00;
    init_timer(&info->watchdog);
    info->watchdog.function = &ei_watchdog;
    info->watchdog.data = (u_long)dev;
    info->watchdog.expires = jiffies + HZ;
    add_timer(&info->watchdog);

    return ax_open(dev);
}