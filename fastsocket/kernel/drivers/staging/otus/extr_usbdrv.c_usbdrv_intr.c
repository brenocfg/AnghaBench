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
struct usbdrv_private {scalar_t__ driver_isolated; } ;
struct pt_regs {int dummy; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

irqreturn_t usbdrv_intr(int irq, void *dev_inst, struct pt_regs *regs)
{
    struct net_device *dev;
    struct usbdrv_private *macp;

    dev = dev_inst;
    macp = dev->ml_priv;


    /* Read register error, card may be unpluged */
    if (0)//(intr_status == -1)
        return IRQ_NONE;

    /* the device is closed, don't continue or else bad things may happen. */
    if (!netif_running(dev)) {
        return IRQ_NONE;
    }

    if (macp->driver_isolated) {
        return IRQ_NONE;
    }

#if (WLAN_HOSTIF == WLAN_PCI)
    //zfiIsrPci(dev);
#endif

    return IRQ_HANDLED;
}