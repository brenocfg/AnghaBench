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
struct mv64xxx_i2c_data {int block; int rc; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  action; int /*<<< orphan*/  bytes_left; TYPE_1__* msg; } ;
struct i2c_msg {int flags; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int I2C_M_NOSTART ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  MV64XXX_I2C_ACTION_CONTINUE ; 
 int /*<<< orphan*/  MV64XXX_I2C_ACTION_SEND_DATA ; 
 int /*<<< orphan*/  MV64XXX_I2C_ACTION_SEND_START ; 
 int /*<<< orphan*/  MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_ACK ; 
 int /*<<< orphan*/  MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_DATA ; 
 int /*<<< orphan*/  MV64XXX_I2C_STATE_WAITING_FOR_START_COND ; 
 int /*<<< orphan*/  mv64xxx_i2c_do_action (struct mv64xxx_i2c_data*) ; 
 int /*<<< orphan*/  mv64xxx_i2c_prepare_for_io (struct mv64xxx_i2c_data*,struct i2c_msg*) ; 
 int /*<<< orphan*/  mv64xxx_i2c_wait_for_completion (struct mv64xxx_i2c_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
mv64xxx_i2c_execute_msg(struct mv64xxx_i2c_data *drv_data, struct i2c_msg *msg)
{
	unsigned long	flags;

	spin_lock_irqsave(&drv_data->lock, flags);
	mv64xxx_i2c_prepare_for_io(drv_data, msg);

	if (unlikely(msg->flags & I2C_M_NOSTART)) { /* Skip start/addr phases */
		if (drv_data->msg->flags & I2C_M_RD) {
			/* No action to do, wait for slave to send a byte */
			drv_data->action = MV64XXX_I2C_ACTION_CONTINUE;
			drv_data->state =
				MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_DATA;
		} else {
			drv_data->action = MV64XXX_I2C_ACTION_SEND_DATA;
			drv_data->state =
				MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_ACK;
			drv_data->bytes_left--;
		}
	} else {
		drv_data->action = MV64XXX_I2C_ACTION_SEND_START;
		drv_data->state = MV64XXX_I2C_STATE_WAITING_FOR_START_COND;
	}

	drv_data->block = 1;
	mv64xxx_i2c_do_action(drv_data);
	spin_unlock_irqrestore(&drv_data->lock, flags);

	mv64xxx_i2c_wait_for_completion(drv_data);
	return drv_data->rc;
}