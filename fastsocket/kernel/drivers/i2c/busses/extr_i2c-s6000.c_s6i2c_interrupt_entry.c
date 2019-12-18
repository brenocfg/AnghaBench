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
struct s6i2c_if {int /*<<< orphan*/  lock; int /*<<< orphan*/  timeout_timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int S6_I2C_INTR_ACTIVITY ; 
 int S6_I2C_INTR_GENCALL ; 
 int S6_I2C_INTR_RDREQ ; 
 int S6_I2C_INTR_RXDONE ; 
 int S6_I2C_INTR_RXFULL ; 
 int S6_I2C_INTR_RXOVER ; 
 int S6_I2C_INTR_RXUNDER ; 
 int S6_I2C_INTR_STARTDET ; 
 int S6_I2C_INTR_STOPDET ; 
 int S6_I2C_INTR_TXABRT ; 
 int S6_I2C_INTR_TXEMPTY ; 
 int S6_I2C_INTR_TXOVER ; 
 int /*<<< orphan*/  S6_I2C_STATUS ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int i2c_rd16 (struct s6i2c_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6i2c_handle_interrupt (struct s6i2c_if*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t s6i2c_interrupt_entry(int irq, void *dev_id)
{
	struct s6i2c_if *iface = dev_id;
	if (!(i2c_rd16(iface, S6_I2C_STATUS) & ((1 << S6_I2C_INTR_RXUNDER)
					      | (1 << S6_I2C_INTR_RXOVER)
					      | (1 << S6_I2C_INTR_RXFULL)
					      | (1 << S6_I2C_INTR_TXOVER)
					      | (1 << S6_I2C_INTR_TXEMPTY)
					      | (1 << S6_I2C_INTR_RDREQ)
					      | (1 << S6_I2C_INTR_TXABRT)
					      | (1 << S6_I2C_INTR_RXDONE)
					      | (1 << S6_I2C_INTR_ACTIVITY)
					      | (1 << S6_I2C_INTR_STOPDET)
					      | (1 << S6_I2C_INTR_STARTDET)
					      | (1 << S6_I2C_INTR_GENCALL))))
		return IRQ_NONE;

	spin_lock(&iface->lock);
	del_timer(&iface->timeout_timer);
	s6i2c_handle_interrupt(iface);
	spin_unlock(&iface->lock);
	return IRQ_HANDLED;
}