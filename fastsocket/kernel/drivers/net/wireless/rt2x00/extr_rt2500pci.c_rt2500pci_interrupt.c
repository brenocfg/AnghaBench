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
struct rt2x00_dev {int /*<<< orphan*/  irqmask_lock; int /*<<< orphan*/  txstatus_tasklet; int /*<<< orphan*/  rxdone_tasklet; int /*<<< orphan*/  tbtt_tasklet; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR7 ; 
 int /*<<< orphan*/  CSR7_RXDONE ; 
 int /*<<< orphan*/  CSR7_TBCN_EXPIRE ; 
 int /*<<< orphan*/  CSR7_TXDONE_ATIMRING ; 
 int /*<<< orphan*/  CSR7_TXDONE_PRIORING ; 
 int /*<<< orphan*/  CSR7_TXDONE_TXRING ; 
 int /*<<< orphan*/  CSR8 ; 
 int /*<<< orphan*/  CSR8_TXDONE_ATIMRING ; 
 int /*<<< orphan*/  CSR8_TXDONE_PRIORING ; 
 int /*<<< orphan*/  CSR8_TXDONE_TXRING ; 
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rt2500pci_interrupt(int irq, void *dev_instance)
{
	struct rt2x00_dev *rt2x00dev = dev_instance;
	u32 reg, mask;

	/*
	 * Get the interrupt sources & saved to local variable.
	 * Write register value back to clear pending interrupts.
	 */
	rt2x00mmio_register_read(rt2x00dev, CSR7, &reg);
	rt2x00mmio_register_write(rt2x00dev, CSR7, reg);

	if (!reg)
		return IRQ_NONE;

	if (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		return IRQ_HANDLED;

	mask = reg;

	/*
	 * Schedule tasklets for interrupt handling.
	 */
	if (rt2x00_get_field32(reg, CSR7_TBCN_EXPIRE))
		tasklet_hi_schedule(&rt2x00dev->tbtt_tasklet);

	if (rt2x00_get_field32(reg, CSR7_RXDONE))
		tasklet_schedule(&rt2x00dev->rxdone_tasklet);

	if (rt2x00_get_field32(reg, CSR7_TXDONE_ATIMRING) ||
	    rt2x00_get_field32(reg, CSR7_TXDONE_PRIORING) ||
	    rt2x00_get_field32(reg, CSR7_TXDONE_TXRING)) {
		tasklet_schedule(&rt2x00dev->txstatus_tasklet);
		/*
		 * Mask out all txdone interrupts.
		 */
		rt2x00_set_field32(&mask, CSR8_TXDONE_TXRING, 1);
		rt2x00_set_field32(&mask, CSR8_TXDONE_ATIMRING, 1);
		rt2x00_set_field32(&mask, CSR8_TXDONE_PRIORING, 1);
	}

	/*
	 * Disable all interrupts for which a tasklet was scheduled right now,
	 * the tasklet will reenable the appropriate interrupts.
	 */
	spin_lock(&rt2x00dev->irqmask_lock);

	rt2x00mmio_register_read(rt2x00dev, CSR8, &reg);
	reg |= mask;
	rt2x00mmio_register_write(rt2x00dev, CSR8, reg);

	spin_unlock(&rt2x00dev->irqmask_lock);

	return IRQ_HANDLED;
}