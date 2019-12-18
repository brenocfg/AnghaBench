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
typedef  int /*<<< orphan*/  u16 ;
struct highlander_i2c_dev {int buf_len; scalar_t__ last_read_time; int /*<<< orphan*/  buf; int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ SMTRDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  highlander_i2c_start (struct highlander_i2c_dev*) ; 
 scalar_t__ highlander_i2c_wait_for_bbsy (struct highlander_i2c_dev*) ; 
 scalar_t__ highlander_i2c_wait_xfer_done (struct highlander_i2c_dev*) ; 
 scalar_t__ iic_read_delay ; 
 int /*<<< orphan*/  ioread16 (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smbus_read_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int highlander_i2c_read(struct highlander_i2c_dev *dev)
{
	int i, cnt;
	u16 data[16];

	if (highlander_i2c_wait_for_bbsy(dev))
		return -EAGAIN;

	highlander_i2c_start(dev);

	if (highlander_i2c_wait_xfer_done(dev)) {
		dev_err(dev->dev, "Arbitration loss\n");
		return -EAGAIN;
	}

	/*
	 * The R0P7780LC0011RL FPGA needs a significant delay between
	 * data read cycles, otherwise the transciever gets confused and
	 * garbage is returned when the read is subsequently aborted.
	 *
	 * It is not sufficient to wait for BBSY.
	 *
	 * While this generally only applies to the older SH7780-based
	 * Highlanders, the same issue can be observed on SH7785 ones,
	 * albeit less frequently. SH7780-based Highlanders may need
	 * this to be as high as 1000 ms.
	 */
	if (iic_read_delay && time_before(jiffies, dev->last_read_time +
				 msecs_to_jiffies(iic_read_delay)))
		msleep(jiffies_to_msecs((dev->last_read_time +
				msecs_to_jiffies(iic_read_delay)) - jiffies));

	cnt = (dev->buf_len + 1) >> 1;
	for (i = 0; i < cnt; i++) {
		data[i] = ioread16(dev->base + SMTRDR + (i * sizeof(u16)));
		dev_dbg(dev->dev, "read data[%x] 0x%04x\n", i, data[i]);
	}

	smbus_read_data(data, dev->buf, dev->buf_len);

	dev->last_read_time = jiffies;

	return 0;
}