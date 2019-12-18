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
struct stu300_dev {scalar_t__ virtbase; TYPE_1__* pdev; } ;
struct i2c_msg {int flags; int addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ I2C_CR ; 
 int I2C_CR_PERIPHERAL_ENABLE ; 
 scalar_t__ I2C_DR ; 
 int I2C_DR_D_MASK ; 
 int I2C_M_RD ; 
 int I2C_M_TEN ; 
 int /*<<< orphan*/  STU300_EVENT_6 ; 
 int /*<<< orphan*/  STU300_EVENT_9 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int stu300_await_event (struct stu300_dev*,int /*<<< orphan*/ ) ; 
 int stu300_r8 (scalar_t__) ; 
 int /*<<< orphan*/  stu300_wr8 (int,scalar_t__) ; 

__attribute__((used)) static int stu300_send_address(struct stu300_dev *dev,
				 struct i2c_msg *msg, int resend)
{
	u32 val;
	int ret;

	if (msg->flags & I2C_M_TEN)
		/* This is probably how 10 bit addresses look */
		val = (0xf0 | (((u32) msg->addr & 0x300) >> 7)) &
			I2C_DR_D_MASK;
	else
		val = ((msg->addr << 1) & I2C_DR_D_MASK);

	if (msg->flags & I2C_M_RD) {
		/* This is the direction bit */
		val |= 0x01;
		if (resend)
			dev_dbg(&dev->pdev->dev, "read resend\n");
	} else if (resend)
		dev_dbg(&dev->pdev->dev, "write resend\n");
	stu300_wr8(val, dev->virtbase + I2C_DR);

	/* For 10bit addressing, await 10bit request (EVENT 9) */
	if (msg->flags & I2C_M_TEN) {
		ret = stu300_await_event(dev, STU300_EVENT_9);
		/*
		 * The slave device wants a 10bit address, send the rest
		 * of the bits (the LSBits)
		 */
		val = msg->addr & I2C_DR_D_MASK;
		/* This clears "event 9" */
		stu300_wr8(val, dev->virtbase + I2C_DR);
		if (ret != 0)
			return ret;
	}
	/* FIXME: Why no else here? two events for 10bit?
	 * Await event 6 (normal) or event 9 (10bit)
	 */

	if (resend)
		dev_dbg(&dev->pdev->dev, "await event 6\n");
	ret = stu300_await_event(dev, STU300_EVENT_6);

	/*
	 * Clear any pending EVENT 6 no matter what happend during
	 * await_event.
	 */
	val = stu300_r8(dev->virtbase + I2C_CR);
	val |= I2C_CR_PERIPHERAL_ENABLE;
	stu300_wr8(val, dev->virtbase + I2C_CR);

	return ret;
}