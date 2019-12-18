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
struct i2c_algo_sgi_data {int xfer_timeout; int (* getctrl ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; int /*<<< orphan*/  (* setctrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int SGI_I2C_BUS_ERR ; 
 int /*<<< orphan*/  SGI_I2C_FORCE_IDLE ; 
 int SGI_I2C_NOT_IDLE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int force_idle(struct i2c_algo_sgi_data *adap)
{
	int i;

	adap->setctrl(adap->data, SGI_I2C_FORCE_IDLE);
	for (i = 0; i < adap->xfer_timeout; i++) {
		if ((adap->getctrl(adap->data) & SGI_I2C_NOT_IDLE) == 0)
			goto out;
		udelay(1);
	}
	return -ETIMEDOUT;
out:
	if (adap->getctrl(adap->data) & SGI_I2C_BUS_ERR)
		return -EIO;
	return 0;
}