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
struct usbdrv_private {int /*<<< orphan*/  device; int /*<<< orphan*/  isolate_lock; int /*<<< orphan*/  driver_isolated; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

void
usbdrv_isolate_driver(struct usbdrv_private *macp)
{
#ifndef CONFIG_SMP
    write_lock_irq(&(macp->isolate_lock));
#endif
    macp->driver_isolated = TRUE;
#ifndef CONFIG_SMP
    write_unlock_irq(&(macp->isolate_lock));
#endif

    if (netif_running(macp->device))
    {
        netif_carrier_off(macp->device);
        netif_stop_queue(macp->device);
    }
}