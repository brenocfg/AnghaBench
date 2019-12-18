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
typedef  int u16 ;
struct highlander_i2c_dev {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SMCR ; 
 int SMCR_IRIC ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iic_timeout ; 
 int ioread16 (scalar_t__) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void highlander_i2c_poll(struct highlander_i2c_dev *dev)
{
	unsigned long timeout;
	u16 smcr;

	timeout = jiffies + msecs_to_jiffies(iic_timeout);
	for (;;) {
		smcr = ioread16(dev->base + SMCR);

		/*
		 * Don't bother checking ACKE here, this and the reset
		 * are handled in highlander_i2c_wait_xfer_done() when
		 * waiting for the ACK.
		 */

		if (smcr & SMCR_IRIC)
			return;
		if (time_after(jiffies, timeout))
			break;

		cpu_relax();
		cond_resched();
	}

	dev_err(dev->dev, "polling timed out\n");
}