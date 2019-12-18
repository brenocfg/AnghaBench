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
typedef  int u32 ;
struct i2c_pnx_algo_data {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; struct i2c_pnx_algo_data* algo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_PNX_TIMEOUT ; 
 int /*<<< orphan*/  I2C_REG_CTL (struct i2c_pnx_algo_data*) ; 
 int /*<<< orphan*/  I2C_REG_STS (struct i2c_pnx_algo_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int mcntrl_reset ; 
 int mstatus_active ; 
 int mstatus_nai ; 
 int mstatus_rfe ; 
 int mstatus_tfe ; 
 int /*<<< orphan*/  wait_reset (int /*<<< orphan*/ ,struct i2c_pnx_algo_data*) ; 

__attribute__((used)) static inline void bus_reset_if_active(struct i2c_adapter *adap)
{
	struct i2c_pnx_algo_data *alg_data = adap->algo_data;
	u32 stat;

	if ((stat = ioread32(I2C_REG_STS(alg_data))) & mstatus_active) {
		dev_err(&adap->dev,
			"%s: Bus is still active after xfer. Reset it...\n",
		       adap->name);
		iowrite32(ioread32(I2C_REG_CTL(alg_data)) | mcntrl_reset,
			  I2C_REG_CTL(alg_data));
		wait_reset(I2C_PNX_TIMEOUT, alg_data);
	} else if (!(stat & mstatus_rfe) || !(stat & mstatus_tfe)) {
		/* If there is data in the fifo's after transfer,
		 * flush fifo's by reset.
		 */
		iowrite32(ioread32(I2C_REG_CTL(alg_data)) | mcntrl_reset,
			  I2C_REG_CTL(alg_data));
		wait_reset(I2C_PNX_TIMEOUT, alg_data);
	} else if (stat & mstatus_nai) {
		iowrite32(ioread32(I2C_REG_CTL(alg_data)) | mcntrl_reset,
			  I2C_REG_CTL(alg_data));
		wait_reset(I2C_PNX_TIMEOUT, alg_data);
	}
}