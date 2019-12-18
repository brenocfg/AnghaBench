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
typedef  int u8_t ;
struct TYPE_2__ {unsigned long data; void* function; } ;
struct usbdrv_private {TYPE_1__ hbTimer10ms; int /*<<< orphan*/  cs_lock; } ;
struct net_device {int* dev_addr; int /*<<< orphan*/  flags; int /*<<< orphan*/ * netdev_ops; struct iw_handler_def* wireless_handlers; } ;
struct iw_handler_def {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_MULTICAST ; 
 void** addr ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  otus_netdev_ops ; 
 int /*<<< orphan*/  p80211wext_handler_def ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfLnx10msTimer ; 
 int /*<<< orphan*/  zfLnxInitVapStruct () ; 
 int /*<<< orphan*/  zfiWlanQueryMacAddress (struct net_device*,void**) ; 

u8_t zfLnxInitSetup(struct net_device *dev, struct usbdrv_private *macp)
{
    //unsigned char addr[6];

    //init_MUTEX(&macp->ps_sem);
    //init_MUTEX(&macp->reg_sem);
    //init_MUTEX(&macp->bcn_sem);
    //init_MUTEX(&macp->config_sem);

    spin_lock_init(&(macp->cs_lock));
#if 0
    /* MAC address */
    zfiWlanQueryMacAddress(dev, addr);
    dev->dev_addr[0] = addr[0];
    dev->dev_addr[1] = addr[1];
    dev->dev_addr[2] = addr[2];
    dev->dev_addr[3] = addr[3];
    dev->dev_addr[4] = addr[4];
    dev->dev_addr[5] = addr[5];
#endif
    dev->wireless_handlers = (struct iw_handler_def *)&p80211wext_handler_def;

    dev->netdev_ops = &otus_netdev_ops;

    dev->flags |= IFF_MULTICAST;

    dev->dev_addr[0] = 0x00;
    dev->dev_addr[1] = 0x03;
    dev->dev_addr[2] = 0x7f;
    dev->dev_addr[3] = 0x11;
    dev->dev_addr[4] = 0x22;
    dev->dev_addr[5] = 0x33;

    /* Initialize Heart Beat timer */
    init_timer(&macp->hbTimer10ms);
    macp->hbTimer10ms.data = (unsigned long)dev;
    macp->hbTimer10ms.function = (void *)&zfLnx10msTimer;

    /* Initialize WDS and VAP data structure */
    //zfInitWdsStruct();
    zfLnxInitVapStruct();

    return 1;
}