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
struct i2c_msg {int dummy; } ;
struct i2c_algo_iop3xx_data {int dummy; } ;
struct i2c_adapter {struct i2c_algo_iop3xx_data* algo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  iop3xx_i2c_enable (struct i2c_algo_iop3xx_data*) ; 
 int iop3xx_i2c_handle_msg (struct i2c_adapter*,struct i2c_msg*) ; 
 int /*<<< orphan*/  iop3xx_i2c_reset (struct i2c_algo_iop3xx_data*) ; 
 int /*<<< orphan*/  iop3xx_i2c_transaction_cleanup (struct i2c_algo_iop3xx_data*) ; 
 int /*<<< orphan*/  iop3xx_i2c_wait_idle (struct i2c_algo_iop3xx_data*,int*) ; 

__attribute__((used)) static int 
iop3xx_i2c_master_xfer(struct i2c_adapter *i2c_adap, struct i2c_msg *msgs, 
				int num)
{
	struct i2c_algo_iop3xx_data *iop3xx_adap = i2c_adap->algo_data;
	int im = 0;
	int ret = 0;
	int status;

	iop3xx_i2c_wait_idle(iop3xx_adap, &status);
	iop3xx_i2c_reset(iop3xx_adap);
	iop3xx_i2c_enable(iop3xx_adap);

	for (im = 0; ret == 0 && im != num; im++) {
		ret = iop3xx_i2c_handle_msg(i2c_adap, &msgs[im]);
	}

	iop3xx_i2c_transaction_cleanup(iop3xx_adap);
	
	if(ret)
		return ret;

	return im;   
}