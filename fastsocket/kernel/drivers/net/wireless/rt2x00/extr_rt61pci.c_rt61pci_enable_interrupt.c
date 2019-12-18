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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_field32 {int dummy; } ;
struct rt2x00_dev {int /*<<< orphan*/  irqmask_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK_CSR ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,struct rt2x00_field32,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rt61pci_enable_interrupt(struct rt2x00_dev *rt2x00dev,
					    struct rt2x00_field32 irq_field)
{
	u32 reg;

	/*
	 * Enable a single interrupt. The interrupt mask register
	 * access needs locking.
	 */
	spin_lock_irq(&rt2x00dev->irqmask_lock);

	rt2x00mmio_register_read(rt2x00dev, INT_MASK_CSR, &reg);
	rt2x00_set_field32(&reg, irq_field, 0);
	rt2x00mmio_register_write(rt2x00dev, INT_MASK_CSR, reg);

	spin_unlock_irq(&rt2x00dev->irqmask_lock);
}