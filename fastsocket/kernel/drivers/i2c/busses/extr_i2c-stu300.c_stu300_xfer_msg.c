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
struct stu300_dev {int /*<<< orphan*/  clk; scalar_t__ virtbase; TYPE_1__* pdev; int /*<<< orphan*/  msg_len; int /*<<< orphan*/  msg_index; } ;
struct i2c_msg {int len; int flags; int* buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ I2C_CR ; 
 int I2C_CR_ACK_ENABLE ; 
 int I2C_CR_PERIPHERAL_ENABLE ; 
 int I2C_CR_START_ENABLE ; 
 int I2C_CR_STOP_ENABLE ; 
 scalar_t__ I2C_DR ; 
 int I2C_M_IGNORE_NAK ; 
 int I2C_M_NOSTART ; 
 int I2C_M_RD ; 
 scalar_t__ I2C_SR1 ; 
 scalar_t__ I2C_SR2 ; 
 int I2C_SR2_AF_IND ; 
 int NUM_ADDR_RESEND_ATTEMPTS ; 
 int /*<<< orphan*/  STU300_EVENT_5 ; 
 int /*<<< orphan*/  STU300_EVENT_7 ; 
 int /*<<< orphan*/  STU300_EVENT_8 ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct stu300_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int stu300_await_event (struct stu300_dev*,int /*<<< orphan*/ ) ; 
 int stu300_init_hw (struct stu300_dev*) ; 
 int stu300_r8 (scalar_t__) ; 
 int stu300_send_address (struct stu300_dev*,struct i2c_msg*,int) ; 
 int stu300_start_and_await_event (struct stu300_dev*,int,int /*<<< orphan*/ ) ; 
 int stu300_wait_while_busy (struct stu300_dev*) ; 
 int /*<<< orphan*/  stu300_wr8 (int,scalar_t__) ; 

__attribute__((used)) static int stu300_xfer_msg(struct i2c_adapter *adap,
			     struct i2c_msg *msg, int stop)
{
	u32 cr;
	u32 val;
	u32 i;
	int ret;
	int attempts = 0;
	struct stu300_dev *dev = i2c_get_adapdata(adap);

	clk_enable(dev->clk);

	/* Remove this if (0) to trace each and every message. */
	if (0) {
		dev_dbg(&dev->pdev->dev, "I2C message to: 0x%04x, len: %d, "
			"flags: 0x%04x, stop: %d\n",
			msg->addr, msg->len, msg->flags, stop);
	}

	/* Zero-length messages are not supported by this hardware */
	if (msg->len == 0) {
		ret = -EINVAL;
		goto exit_disable;
	}

	/*
	 * For some reason, sending the address sometimes fails when running
	 * on  the 13 MHz clock. No interrupt arrives. This is a work around,
	 * which tries to restart and send the address up to 10 times before
	 * really giving up. Usually 5 to 8 attempts are enough.
	 */
	do {
		if (attempts)
			dev_dbg(&dev->pdev->dev, "wait while busy\n");
		/* Check that the bus is free, or wait until some timeout */
		ret = stu300_wait_while_busy(dev);
		if (ret != 0)
			goto exit_disable;

		if (attempts)
			dev_dbg(&dev->pdev->dev, "re-int hw\n");
		/*
		 * According to ST, there is no problem if the clock is
		 * changed between 13 and 26 MHz during a transfer.
		 */
		ret = stu300_init_hw(dev);
		if (ret)
			goto exit_disable;

		/* Send a start condition */
		cr = I2C_CR_PERIPHERAL_ENABLE;
		/* Setting the START bit puts the block in master mode */
		if (!(msg->flags & I2C_M_NOSTART))
			cr |= I2C_CR_START_ENABLE;
		if ((msg->flags & I2C_M_RD) && (msg->len > 1))
			/* On read more than 1 byte, we need ack. */
			cr |= I2C_CR_ACK_ENABLE;
		/* Check that it gets through */
		if (!(msg->flags & I2C_M_NOSTART)) {
			if (attempts)
				dev_dbg(&dev->pdev->dev, "send start event\n");
			ret = stu300_start_and_await_event(dev, cr,
							     STU300_EVENT_5);
		}

		if (attempts)
			dev_dbg(&dev->pdev->dev, "send address\n");

		if (ret == 0)
			/* Send address */
			ret = stu300_send_address(dev, msg, attempts != 0);

		if (ret != 0) {
			attempts++;
			dev_dbg(&dev->pdev->dev, "failed sending address, "
				"retrying. Attempt: %d msg_index: %d/%d\n",
			       attempts, dev->msg_index, dev->msg_len);
		}

	} while (ret != 0 && attempts < NUM_ADDR_RESEND_ATTEMPTS);

	if (attempts < NUM_ADDR_RESEND_ATTEMPTS && attempts > 0) {
		dev_dbg(&dev->pdev->dev, "managed to get address "
			"through after %d attempts\n", attempts);
	} else if (attempts == NUM_ADDR_RESEND_ATTEMPTS) {
		dev_dbg(&dev->pdev->dev, "I give up, tried %d times "
			"to resend address.\n",
			NUM_ADDR_RESEND_ATTEMPTS);
		goto exit_disable;
	}


	if (msg->flags & I2C_M_RD) {
		/* READ: we read the actual bytes one at a time */
		for (i = 0; i < msg->len; i++) {
			if (i == msg->len-1) {
				/*
				 * Disable ACK and set STOP condition before
				 * reading last byte
				 */
				val = I2C_CR_PERIPHERAL_ENABLE;

				if (stop)
					val |= I2C_CR_STOP_ENABLE;

				stu300_wr8(val,
					   dev->virtbase + I2C_CR);
			}
			/* Wait for this byte... */
			ret = stu300_await_event(dev, STU300_EVENT_7);
			if (ret != 0)
				goto exit_disable;
			/* This clears event 7 */
			msg->buf[i] = (u8) stu300_r8(dev->virtbase + I2C_DR);
		}
	} else {
		/* WRITE: we send the actual bytes one at a time */
		for (i = 0; i < msg->len; i++) {
			/* Write the byte */
			stu300_wr8(msg->buf[i],
				   dev->virtbase + I2C_DR);
			/* Check status */
			ret = stu300_await_event(dev, STU300_EVENT_8);
			/* Next write to DR will clear event 8 */
			if (ret != 0) {
				dev_err(&dev->pdev->dev, "error awaiting "
				       "event 8 (%d)\n", ret);
				goto exit_disable;
			}
		}
		/* Check NAK */
		if (!(msg->flags & I2C_M_IGNORE_NAK)) {
			if (stu300_r8(dev->virtbase + I2C_SR2) &
			    I2C_SR2_AF_IND) {
				dev_err(&dev->pdev->dev, "I2C payload "
				       "send returned NAK!\n");
				ret = -EIO;
				goto exit_disable;
			}
		}
		if (stop) {
			/* Send stop condition */
			val = I2C_CR_PERIPHERAL_ENABLE;
			val |= I2C_CR_STOP_ENABLE;
			stu300_wr8(val, dev->virtbase + I2C_CR);
		}
	}

	/* Check that the bus is free, or wait until some timeout occurs */
	ret = stu300_wait_while_busy(dev);
	if (ret != 0) {
		dev_err(&dev->pdev->dev, "timout waiting for transfer "
		       "to commence.\n");
		goto exit_disable;
	}

	/* Dummy read status registers */
	val = stu300_r8(dev->virtbase + I2C_SR2);
	val = stu300_r8(dev->virtbase + I2C_SR1);
	ret = 0;

 exit_disable:
	/* Disable controller */
	stu300_wr8(0x00, dev->virtbase + I2C_CR);
	clk_disable(dev->clk);
	return ret;
}