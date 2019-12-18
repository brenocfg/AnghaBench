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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  complete; int /*<<< orphan*/  ret; } ;
struct i2c_pnx_algo_data {TYPE_1__ mif; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; struct i2c_pnx_algo_data* algo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  I2C_PNX_TIMEOUT ; 
 int /*<<< orphan*/  I2C_REG_CTL (struct i2c_pnx_algo_data*) ; 
 int /*<<< orphan*/  I2C_REG_STS (struct i2c_pnx_algo_data*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int mcntrl_afie ; 
 int mcntrl_drmie ; 
 int mcntrl_naie ; 
 int mcntrl_reset ; 
 int mcntrl_rffie ; 
 int /*<<< orphan*/  wait_reset (int /*<<< orphan*/ ,struct i2c_pnx_algo_data*) ; 

__attribute__((used)) static void i2c_pnx_timeout(unsigned long data)
{
	struct i2c_adapter *adap = (struct i2c_adapter *)data;
	struct i2c_pnx_algo_data *alg_data = adap->algo_data;
	u32 ctl;

	dev_err(&adap->dev, "Master timed out. stat = %04x, cntrl = %04x. "
	       "Resetting master...\n",
	       ioread32(I2C_REG_STS(alg_data)),
	       ioread32(I2C_REG_CTL(alg_data)));

	/* Reset master and disable interrupts */
	ctl = ioread32(I2C_REG_CTL(alg_data));
	ctl &= ~(mcntrl_afie | mcntrl_naie | mcntrl_rffie | mcntrl_drmie);
	iowrite32(ctl, I2C_REG_CTL(alg_data));

	ctl |= mcntrl_reset;
	iowrite32(ctl, I2C_REG_CTL(alg_data));
	wait_reset(I2C_PNX_TIMEOUT, alg_data);
	alg_data->mif.ret = -EIO;
	complete(&alg_data->mif.complete);
}