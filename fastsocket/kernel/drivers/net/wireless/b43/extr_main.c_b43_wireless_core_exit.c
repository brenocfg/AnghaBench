#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ops; } ;
struct b43_wldev {TYPE_3__* wl; TYPE_2__ phy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * current_beacon; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* switch_analog ) (struct b43_wldev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MACCTL_PSM_JMP0 ; 
 int /*<<< orphan*/  B43_MACCTL_PSM_RUN ; 
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 scalar_t__ B43_STAT_INITIALIZED ; 
 int /*<<< orphan*/  B43_STAT_UNINIT ; 
 int /*<<< orphan*/  B43_WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_bus_may_powerdown (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_chip_exit (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_device_disable (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_dma_free (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_maskset32 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_pio_free (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_rng_exit (TYPE_3__*) ; 
 int /*<<< orphan*/  b43_set_status (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 scalar_t__ b43_status (struct b43_wldev*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_wireless_core_exit(struct b43_wldev *dev)
{
	B43_WARN_ON(dev && b43_status(dev) > B43_STAT_INITIALIZED);
	if (!dev || b43_status(dev) != B43_STAT_INITIALIZED)
		return;

	/* Unregister HW RNG driver */
	b43_rng_exit(dev->wl);

	b43_set_status(dev, B43_STAT_UNINIT);

	/* Stop the microcode PSM. */
	b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_PSM_RUN,
		      B43_MACCTL_PSM_JMP0);

	b43_dma_free(dev);
	b43_pio_free(dev);
	b43_chip_exit(dev);
	dev->phy.ops->switch_analog(dev, 0);
	if (dev->wl->current_beacon) {
		dev_kfree_skb_any(dev->wl->current_beacon);
		dev->wl->current_beacon = NULL;
	}

	b43_device_disable(dev, 0);
	b43_bus_may_powerdown(dev);
}