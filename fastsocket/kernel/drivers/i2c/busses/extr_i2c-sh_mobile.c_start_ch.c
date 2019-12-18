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
struct sh_mobile_i2c_data {int iccl; int icch; int pos; scalar_t__ sr; struct i2c_msg* msg; int /*<<< orphan*/  dev; } ;
struct i2c_msg {scalar_t__ len; int flags; } ;

/* Variables and functions */
 int EIO ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  ICCH (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  ICCL (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  ICCR (struct sh_mobile_i2c_data*) ; 
 int ICCR_ICE ; 
 int /*<<< orphan*/  ICIC (struct sh_mobile_i2c_data*) ; 
 int ICIC_ALE ; 
 int ICIC_DTEE ; 
 int ICIC_TACKE ; 
 int ICIC_WAITE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_ch(struct sh_mobile_i2c_data *pd, struct i2c_msg *usr_msg)
{
	if (usr_msg->len == 0 && (usr_msg->flags & I2C_M_RD)) {
		dev_err(pd->dev, "Unsupported zero length i2c read\n");
		return -EIO;
	}

	/* Initialize channel registers */
	iowrite8(ioread8(ICCR(pd)) & ~ICCR_ICE, ICCR(pd));

	/* Enable channel and configure rx ack */
	iowrite8(ioread8(ICCR(pd)) | ICCR_ICE, ICCR(pd));

	/* Set the clock */
	iowrite8(pd->iccl, ICCL(pd));
	iowrite8(pd->icch, ICCH(pd));

	pd->msg = usr_msg;
	pd->pos = -1;
	pd->sr = 0;

	/* Enable all interrupts to begin with */
	iowrite8(ICIC_WAITE | ICIC_ALE | ICIC_TACKE | ICIC_DTEE, ICIC(pd));
	return 0;
}