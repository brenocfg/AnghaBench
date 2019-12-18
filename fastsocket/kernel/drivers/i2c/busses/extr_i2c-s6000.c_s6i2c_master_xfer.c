#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct s6i2c_if {int msgs_num; int msgs_done; int timeout_count; TYPE_1__ timeout_timer; int /*<<< orphan*/  complete; scalar_t__ done; scalar_t__ push; scalar_t__ msgs_push; struct i2c_msg* msgs; } ;
struct i2c_msg {int flags; scalar_t__ len; scalar_t__ addr; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; struct s6i2c_if* algo_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2C_M_TEN ; 
 scalar_t__ POLL_TIMEOUT ; 
 int /*<<< orphan*/  S6_I2C_CLRINTR ; 
 int /*<<< orphan*/  S6_I2C_ENABLE ; 
 int /*<<< orphan*/  S6_I2C_INTRMASK ; 
 int S6_I2C_INTR_TXABRT ; 
 int S6_I2C_INTR_TXEMPTY ; 
 int /*<<< orphan*/  S6_I2C_STATUS ; 
 int S6_I2C_STATUS_ACTIVITY ; 
 int /*<<< orphan*/  S6_I2C_TAR ; 
 int /*<<< orphan*/  S6_I2C_TXFLR ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_rd16 (struct s6i2c_if*,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_rd32 (struct s6i2c_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_wr16 (struct s6i2c_if*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yield () ; 

__attribute__((used)) static int s6i2c_master_xfer(struct i2c_adapter *adap,
				struct i2c_msg *msgs, int num)
{
	struct s6i2c_if *iface = adap->algo_data;
	int i;
	if (num == 0)
		return 0;
	if (i2c_rd16(iface, S6_I2C_STATUS) & (1 << S6_I2C_STATUS_ACTIVITY))
		yield();
	i2c_wr16(iface, S6_I2C_INTRMASK, 0);
	i2c_rd16(iface, S6_I2C_CLRINTR);
	for (i = 0; i < num; i++) {
		if (msgs[i].flags & I2C_M_TEN) {
			dev_err(&adap->dev,
				"s6i2c: 10 bits addr not supported\n");
			return -EINVAL;
		}
		if (msgs[i].len == 0) {
			dev_err(&adap->dev,
				"s6i2c: zero length message not supported\n");
			return -EINVAL;
		}
		if (msgs[i].addr != msgs[0].addr) {
			dev_err(&adap->dev,
				"s6i2c: multiple xfer cannot change target\n");
			return -EINVAL;
		}
	}

	iface->msgs = msgs;
	iface->msgs_num = num;
	iface->msgs_push = 0;
	iface->msgs_done = 0;
	iface->push = 0;
	iface->done = 0;
	iface->timeout_count = 10;
	i2c_wr16(iface, S6_I2C_TAR, msgs[0].addr);
	i2c_wr16(iface, S6_I2C_ENABLE, 1);
	i2c_wr16(iface, S6_I2C_INTRMASK, (1 << S6_I2C_INTR_TXEMPTY) |
					 (1 << S6_I2C_INTR_TXABRT));

	iface->timeout_timer.expires = jiffies + POLL_TIMEOUT;
	add_timer(&iface->timeout_timer);
	wait_for_completion(&iface->complete);
	del_timer_sync(&iface->timeout_timer);
	while (i2c_rd32(iface, S6_I2C_TXFLR) > 0)
		schedule();
	while (i2c_rd16(iface, S6_I2C_STATUS) & (1 << S6_I2C_STATUS_ACTIVITY))
		schedule();

	i2c_wr16(iface, S6_I2C_INTRMASK, 0);
	i2c_wr16(iface, S6_I2C_ENABLE, 0);
	return iface->msgs_done;
}