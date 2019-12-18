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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct i2c_msg {scalar_t__ addr; int flags; scalar_t__ len; int /*<<< orphan*/ * buf; } ;
struct i2c_adapter {int dummy; } ;
struct dw_i2c_dev {int msgs_num; size_t msg_read_idx; int status; scalar_t__ rx_buf_len; int /*<<< orphan*/ * rx_buf; scalar_t__ base; struct i2c_msg* msgs; } ;

/* Variables and functions */
 scalar_t__ DW_IC_DATA_CMD ; 
 scalar_t__ DW_IC_RXFLR ; 
 int I2C_M_RD ; 
 int STATUS_READ_IN_PROGRESS ; 
 struct dw_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static void
i2c_dw_read(struct i2c_adapter *adap)
{
	struct dw_i2c_dev *dev = i2c_get_adapdata(adap);
	struct i2c_msg *msgs = dev->msgs;
	int num = dev->msgs_num;
	u16 addr = msgs[dev->msg_read_idx].addr;
	int rx_valid = readw(dev->base + DW_IC_RXFLR);

	for (; dev->msg_read_idx < num; dev->msg_read_idx++) {
		u16 len;
		u8 *buf;

		if (!(msgs[dev->msg_read_idx].flags & I2C_M_RD))
			continue;

		/* different i2c client, reprogram the i2c adapter */
		if (msgs[dev->msg_read_idx].addr != addr)
			return;

		if (!(dev->status & STATUS_READ_IN_PROGRESS)) {
			len = msgs[dev->msg_read_idx].len;
			buf = msgs[dev->msg_read_idx].buf;
		} else {
			len = dev->rx_buf_len;
			buf = dev->rx_buf;
		}

		for (; len > 0 && rx_valid > 0; len--, rx_valid--)
			*buf++ = readb(dev->base + DW_IC_DATA_CMD);

		if (len > 0) {
			dev->status |= STATUS_READ_IN_PROGRESS;
			dev->rx_buf_len = len;
			dev->rx_buf = buf;
			return;
		} else
			dev->status &= ~STATUS_READ_IN_PROGRESS;
	}
}