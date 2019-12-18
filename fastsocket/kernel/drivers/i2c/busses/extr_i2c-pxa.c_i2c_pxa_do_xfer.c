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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct pxa_i2c {int msg_num; int msg_idx; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; scalar_t__ irqlogidx; scalar_t__ msg_ptr; struct i2c_msg* msg; TYPE_1__ adap; } ;
struct i2c_msg {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  i2c_pxa_scream_blue_murder (struct pxa_i2c*,char*) ; 
 int i2c_pxa_set_master (struct pxa_i2c*) ; 
 int /*<<< orphan*/  i2c_pxa_start_message (struct pxa_i2c*) ; 
 int /*<<< orphan*/  i2c_pxa_stop_message (struct pxa_i2c*) ; 
 int i2c_pxa_wait_bus_not_busy (struct pxa_i2c*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int i2c_pxa_do_xfer(struct pxa_i2c *i2c, struct i2c_msg *msg, int num)
{
	long timeout;
	int ret;

	/*
	 * Wait for the bus to become free.
	 */
	ret = i2c_pxa_wait_bus_not_busy(i2c);
	if (ret) {
		dev_err(&i2c->adap.dev, "i2c_pxa: timeout waiting for bus free\n");
		goto out;
	}

	/*
	 * Set master mode.
	 */
	ret = i2c_pxa_set_master(i2c);
	if (ret) {
		dev_err(&i2c->adap.dev, "i2c_pxa_set_master: error %d\n", ret);
		goto out;
	}

	spin_lock_irq(&i2c->lock);

	i2c->msg = msg;
	i2c->msg_num = num;
	i2c->msg_idx = 0;
	i2c->msg_ptr = 0;
	i2c->irqlogidx = 0;

	i2c_pxa_start_message(i2c);

	spin_unlock_irq(&i2c->lock);

	/*
	 * The rest of the processing occurs in the interrupt handler.
	 */
	timeout = wait_event_timeout(i2c->wait, i2c->msg_num == 0, HZ * 5);
	i2c_pxa_stop_message(i2c);

	/*
	 * We place the return code in i2c->msg_idx.
	 */
	ret = i2c->msg_idx;

	if (timeout == 0)
		i2c_pxa_scream_blue_murder(i2c, "timeout");

 out:
	return ret;
}