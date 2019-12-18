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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct pmac_i2c_host_kw {int speed; scalar_t__ irq; int* data; int len; scalar_t__ state; int result; int rw; int /*<<< orphan*/  lock; int /*<<< orphan*/  complete; TYPE_1__ timeout_timer; int /*<<< orphan*/  polled; } ;
struct pmac_i2c_bus {int mode; int channel; int /*<<< orphan*/  polled; struct pmac_i2c_host_kw* hostdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_COMPLETION (int /*<<< orphan*/ ) ; 
 int KW_I2C_CTL_XADDR ; 
 int KW_I2C_IRQ_MASK ; 
 int KW_I2C_MODE_COMBINED ; 
 int KW_I2C_MODE_MODE_MASK ; 
 int KW_I2C_MODE_STANDARD ; 
 int KW_I2C_MODE_STANDARDSUB ; 
 scalar_t__ KW_POLL_TIMEOUT ; 
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kw_i2c_handle_interrupt (struct pmac_i2c_host_kw*,int) ; 
 int kw_i2c_wait_interrupt (struct pmac_i2c_host_kw*) ; 
 int kw_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kw_write_reg (int /*<<< orphan*/ ,int) ; 
#define  pmac_i2c_mode_combined 131 
#define  pmac_i2c_mode_dumb 130 
#define  pmac_i2c_mode_std 129 
#define  pmac_i2c_mode_stdsub 128 
 int /*<<< orphan*/  reg_addr ; 
 int /*<<< orphan*/  reg_control ; 
 int /*<<< orphan*/  reg_ier ; 
 int /*<<< orphan*/  reg_isr ; 
 int /*<<< orphan*/  reg_mode ; 
 int /*<<< orphan*/  reg_status ; 
 int /*<<< orphan*/  reg_subaddr ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ state_addr ; 
 scalar_t__ state_idle ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kw_i2c_xfer(struct pmac_i2c_bus *bus, u8 addrdir, int subsize,
		       u32 subaddr, u8 *data, int len)
{
	struct pmac_i2c_host_kw *host = bus->hostdata;
	u8 mode_reg = host->speed;
	int use_irq = host->irq != NO_IRQ && !bus->polled;

	/* Setup mode & subaddress if any */
	switch(bus->mode) {
	case pmac_i2c_mode_dumb:
		return -EINVAL;
	case pmac_i2c_mode_std:
		mode_reg |= KW_I2C_MODE_STANDARD;
		if (subsize != 0)
			return -EINVAL;
		break;
	case pmac_i2c_mode_stdsub:
		mode_reg |= KW_I2C_MODE_STANDARDSUB;
		if (subsize != 1)
			return -EINVAL;
		break;
	case pmac_i2c_mode_combined:
		mode_reg |= KW_I2C_MODE_COMBINED;
		if (subsize != 1)
			return -EINVAL;
		break;
	}

	/* Setup channel & clear pending irqs */
	kw_write_reg(reg_isr, kw_read_reg(reg_isr));
	kw_write_reg(reg_mode, mode_reg | (bus->channel << 4));
	kw_write_reg(reg_status, 0);

	/* Set up address and r/w bit, strip possible stale bus number from
	 * address top bits
	 */
	kw_write_reg(reg_addr, addrdir & 0xff);

	/* Set up the sub address */
	if ((mode_reg & KW_I2C_MODE_MODE_MASK) == KW_I2C_MODE_STANDARDSUB
	    || (mode_reg & KW_I2C_MODE_MODE_MASK) == KW_I2C_MODE_COMBINED)
		kw_write_reg(reg_subaddr, subaddr);

	/* Prepare for async operations */
	host->data = data;
	host->len = len;
	host->state = state_addr;
	host->result = 0;
	host->rw = (addrdir & 1);
	host->polled = bus->polled;

	/* Enable interrupt if not using polled mode and interrupt is
	 * available
	 */
	if (use_irq) {
		/* Clear completion */
		INIT_COMPLETION(host->complete);
		/* Ack stale interrupts */
		kw_write_reg(reg_isr, kw_read_reg(reg_isr));
		/* Arm timeout */
		host->timeout_timer.expires = jiffies + KW_POLL_TIMEOUT;
		add_timer(&host->timeout_timer);
		/* Enable emission */
		kw_write_reg(reg_ier, KW_I2C_IRQ_MASK);
	}

	/* Start sending address */
	kw_write_reg(reg_control, KW_I2C_CTL_XADDR);

	/* Wait for completion */
	if (use_irq)
		wait_for_completion(&host->complete);
	else {
		while(host->state != state_idle) {
			unsigned long flags;

			u8 isr = kw_i2c_wait_interrupt(host);
			spin_lock_irqsave(&host->lock, flags);
			kw_i2c_handle_interrupt(host, isr);
			spin_unlock_irqrestore(&host->lock, flags);
		}
	}

	/* Disable emission */
	kw_write_reg(reg_ier, 0);

	return host->result;
}