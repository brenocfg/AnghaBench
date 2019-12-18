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
typedef  int u32 ;
struct b43legacy_wldev {scalar_t__ mac_suspended; TYPE_1__* wl; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int B43legacy_IRQ_MAC_SUSPENDED ; 
 int B43legacy_MACCTL_ENABLED ; 
 int /*<<< orphan*/  B43legacy_MMIO_GEN_IRQ_MASK ; 
 int /*<<< orphan*/  B43legacy_MMIO_GEN_IRQ_REASON ; 
 int /*<<< orphan*/  B43legacy_MMIO_MACCTL ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  b43legacy_power_saving_ctl_bits (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_synchronize_irq (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacyerr (TYPE_1__*,char*) ; 
 int irqs_disabled () ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void b43legacy_mac_suspend(struct b43legacy_wldev *dev)
{
	int i;
	u32 tmp;

	might_sleep();
	B43legacy_WARN_ON(irqs_disabled());
	B43legacy_WARN_ON(dev->mac_suspended < 0);

	if (dev->mac_suspended == 0) {
		/* Mask IRQs before suspending MAC. Otherwise
		 * the MAC stays busy and won't suspend. */
		spin_lock_irq(&dev->wl->irq_lock);
		b43legacy_write32(dev, B43legacy_MMIO_GEN_IRQ_MASK, 0);
		spin_unlock_irq(&dev->wl->irq_lock);
		b43legacy_synchronize_irq(dev);

		b43legacy_power_saving_ctl_bits(dev, -1, 1);
		b43legacy_write32(dev, B43legacy_MMIO_MACCTL,
				  b43legacy_read32(dev,
				  B43legacy_MMIO_MACCTL)
				  & ~B43legacy_MACCTL_ENABLED);
		b43legacy_read32(dev, B43legacy_MMIO_GEN_IRQ_REASON);
		for (i = 40; i; i--) {
			tmp = b43legacy_read32(dev,
					       B43legacy_MMIO_GEN_IRQ_REASON);
			if (tmp & B43legacy_IRQ_MAC_SUSPENDED)
				goto out;
			msleep(1);
		}
		b43legacyerr(dev->wl, "MAC suspend failed\n");
	}
out:
	dev->mac_suspended++;
}