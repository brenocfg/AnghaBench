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
struct i2c_algo_sgi_data {int (* getctrl ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; int /*<<< orphan*/  (* wdata ) (int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  (* setctrl ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EIO ; 
 int SGI_I2C_HOLD_BUS ; 
 int SGI_I2C_NOT_IDLE ; 
 int SGI_I2C_WRITE ; 
 scalar_t__ force_idle (struct i2c_algo_sgi_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ wait_ack (struct i2c_algo_sgi_data*) ; 

__attribute__((used)) static int do_address(struct i2c_algo_sgi_data *adap, unsigned int addr,
		      int rd)
{
	if (rd)
		adap->setctrl(adap->data, SGI_I2C_NOT_IDLE);
	/* Check if bus is idle, eventually force it to do so */
	if (adap->getctrl(adap->data) & SGI_I2C_NOT_IDLE)
		if (force_idle(adap))
			return -EIO;
	/* Write out the i2c chip address and specify operation */
	adap->setctrl(adap->data,
		      SGI_I2C_HOLD_BUS | SGI_I2C_WRITE | SGI_I2C_NOT_IDLE);
	if (rd)
		addr |= 1;
	adap->wdata(adap->data, addr);
	if (wait_ack(adap))
		return -EIO;
	return 0;
}