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
struct rt2x00_dev {int /*<<< orphan*/  irqmask_lock; int /*<<< orphan*/  autowake_tasklet; int /*<<< orphan*/  tbtt_tasklet; int /*<<< orphan*/  txstatus_tasklet; int /*<<< orphan*/  rxdone_tasklet; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  INT_MASK_CSR ; 
 int /*<<< orphan*/  INT_SOURCE_CSR ; 
 int /*<<< orphan*/  INT_SOURCE_CSR_BEACON_DONE ; 
 int /*<<< orphan*/  INT_SOURCE_CSR_RXDONE ; 
 int /*<<< orphan*/  INT_SOURCE_CSR_TXDONE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR ; 
 int /*<<< orphan*/  MCU_INT_SOURCE_CSR ; 
 int /*<<< orphan*/  MCU_INT_SOURCE_CSR_TWAKEUP ; 
 scalar_t__ rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rt61pci_interrupt(int irq, void *dev_instance)
{
	struct rt2x00_dev *rt2x00dev = dev_instance;
	u32 reg_mcu, mask_mcu;
	u32 reg, mask;

	/*
	 * Get the interrupt sources & saved to local variable.
	 * Write register value back to clear pending interrupts.
	 */
	rt2x00mmio_register_read(rt2x00dev, MCU_INT_SOURCE_CSR, &reg_mcu);
	rt2x00mmio_register_write(rt2x00dev, MCU_INT_SOURCE_CSR, reg_mcu);

	rt2x00mmio_register_read(rt2x00dev, INT_SOURCE_CSR, &reg);
	rt2x00mmio_register_write(rt2x00dev, INT_SOURCE_CSR, reg);

	if (!reg && !reg_mcu)
		return IRQ_NONE;

	if (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		return IRQ_HANDLED;

	/*
	 * Schedule tasklets for interrupt handling.
	 */
	if (rt2x00_get_field32(reg, INT_SOURCE_CSR_RXDONE))
		tasklet_schedule(&rt2x00dev->rxdone_tasklet);

	if (rt2x00_get_field32(reg, INT_SOURCE_CSR_TXDONE))
		tasklet_schedule(&rt2x00dev->txstatus_tasklet);

	if (rt2x00_get_field32(reg, INT_SOURCE_CSR_BEACON_DONE))
		tasklet_hi_schedule(&rt2x00dev->tbtt_tasklet);

	if (rt2x00_get_field32(reg_mcu, MCU_INT_SOURCE_CSR_TWAKEUP))
		tasklet_schedule(&rt2x00dev->autowake_tasklet);

	/*
	 * Since INT_MASK_CSR and INT_SOURCE_CSR use the same bits
	 * for interrupts and interrupt masks we can just use the value of
	 * INT_SOURCE_CSR to create the interrupt mask.
	 */
	mask = reg;
	mask_mcu = reg_mcu;

	/*
	 * Disable all interrupts for which a tasklet was scheduled right now,
	 * the tasklet will reenable the appropriate interrupts.
	 */
	spin_lock(&rt2x00dev->irqmask_lock);

	rt2x00mmio_register_read(rt2x00dev, INT_MASK_CSR, &reg);
	reg |= mask;
	rt2x00mmio_register_write(rt2x00dev, INT_MASK_CSR, reg);

	rt2x00mmio_register_read(rt2x00dev, MCU_INT_MASK_CSR, &reg);
	reg |= mask_mcu;
	rt2x00mmio_register_write(rt2x00dev, MCU_INT_MASK_CSR, reg);

	spin_unlock(&rt2x00dev->irqmask_lock);

	return IRQ_HANDLED;
}