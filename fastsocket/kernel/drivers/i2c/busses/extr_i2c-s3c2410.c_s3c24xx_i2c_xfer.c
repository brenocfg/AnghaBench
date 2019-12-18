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
struct s3c24xx_i2c {int /*<<< orphan*/  dev; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int retries; scalar_t__ algo_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int s3c24xx_i2c_doxfer (struct s3c24xx_i2c*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int s3c24xx_i2c_xfer(struct i2c_adapter *adap,
			struct i2c_msg *msgs, int num)
{
	struct s3c24xx_i2c *i2c = (struct s3c24xx_i2c *)adap->algo_data;
	int retry;
	int ret;

	for (retry = 0; retry < adap->retries; retry++) {

		ret = s3c24xx_i2c_doxfer(i2c, msgs, num);

		if (ret != -EAGAIN)
			return ret;

		dev_dbg(i2c->dev, "Retrying transmission (%d)\n", retry);

		udelay(100);
	}

	return -EREMOTEIO;
}