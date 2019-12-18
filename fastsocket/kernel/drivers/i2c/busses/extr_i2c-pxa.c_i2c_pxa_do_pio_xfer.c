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
struct pxa_i2c {int msg_num; int msg_idx; scalar_t__ irqlogidx; scalar_t__ msg_ptr; struct i2c_msg* msg; } ;
struct i2c_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_pxa_handler (int /*<<< orphan*/ ,struct pxa_i2c*) ; 
 int i2c_pxa_pio_set_master (struct pxa_i2c*) ; 
 int /*<<< orphan*/  i2c_pxa_scream_blue_murder (struct pxa_i2c*,char*) ; 
 int /*<<< orphan*/  i2c_pxa_start_message (struct pxa_i2c*) ; 
 int /*<<< orphan*/  i2c_pxa_stop_message (struct pxa_i2c*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int i2c_pxa_do_pio_xfer(struct pxa_i2c *i2c,
			       struct i2c_msg *msg, int num)
{
	unsigned long timeout = 500000; /* 5 seconds */
	int ret = 0;

	ret = i2c_pxa_pio_set_master(i2c);
	if (ret)
		goto out;

	i2c->msg = msg;
	i2c->msg_num = num;
	i2c->msg_idx = 0;
	i2c->msg_ptr = 0;
	i2c->irqlogidx = 0;

	i2c_pxa_start_message(i2c);

	while (i2c->msg_num > 0 && --timeout) {
		i2c_pxa_handler(0, i2c);
		udelay(10);
	}

	i2c_pxa_stop_message(i2c);

	/*
	 * We place the return code in i2c->msg_idx.
	 */
	ret = i2c->msg_idx;

out:
	if (timeout == 0)
		i2c_pxa_scream_blue_murder(i2c, "timeout");

	return ret;
}