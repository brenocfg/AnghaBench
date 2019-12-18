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
struct pxa_i2c {int dummy; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int retries; int /*<<< orphan*/  dev; struct pxa_i2c* algo_data; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int I2C_RETRY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ i2c_debug ; 
 int i2c_pxa_do_xfer (struct pxa_i2c*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  i2c_pxa_scream_blue_murder (struct pxa_i2c*,char*) ; 
 int /*<<< orphan*/  i2c_pxa_set_slave (struct pxa_i2c*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int i2c_pxa_xfer(struct i2c_adapter *adap, struct i2c_msg msgs[], int num)
{
	struct pxa_i2c *i2c = adap->algo_data;
	int ret, i;

	for (i = adap->retries; i >= 0; i--) {
		ret = i2c_pxa_do_xfer(i2c, msgs, num);
		if (ret != I2C_RETRY)
			goto out;

		if (i2c_debug)
			dev_dbg(&adap->dev, "Retrying transmission\n");
		udelay(100);
	}
	i2c_pxa_scream_blue_murder(i2c, "exhausted retries");
	ret = -EREMOTEIO;
 out:
	i2c_pxa_set_slave(i2c, ret);
	return ret;
}