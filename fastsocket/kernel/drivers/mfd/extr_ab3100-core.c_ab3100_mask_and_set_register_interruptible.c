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
typedef  int /*<<< orphan*/  u8 ;
struct ab3100 {int /*<<< orphan*/  access_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_master_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ab3100_mask_and_set_register_interruptible(struct ab3100 *ab3100,
				 u8 reg, u8 andmask, u8 ormask)
{
	u8 regandval[2] = {reg, 0};
	int err;

	err = mutex_lock_interruptible(&ab3100->access_mutex);
	if (err)
		return err;

	/* First read out the target register */
	err = i2c_master_send(ab3100->i2c_client, &reg, 1);
	if (err < 0) {
		dev_err(ab3100->dev,
			"write error (maskset send address): %d\n",
			err);
		goto get_maskset_unlock;
	} else if (err != 1) {
		dev_err(ab3100->dev,
			"write error (maskset send address) "
			"%d bytes transferred (expected 1)\n",
			err);
		err = -EIO;
		goto get_maskset_unlock;
	}

	err = i2c_master_recv(ab3100->i2c_client, &regandval[1], 1);
	if (err < 0) {
		dev_err(ab3100->dev,
			"write error (maskset read register): %d\n",
			err);
		goto get_maskset_unlock;
	} else if (err != 1) {
		dev_err(ab3100->dev,
			"write error (maskset read register) "
			"%d bytes transferred (expected 1)\n",
			err);
		err = -EIO;
		goto get_maskset_unlock;
	}

	/* Modify the register */
	regandval[1] &= andmask;
	regandval[1] |= ormask;

	/* Write the register */
	err = i2c_master_send(ab3100->i2c_client, regandval, 2);
	if (err < 0) {
		dev_err(ab3100->dev,
			"write error (write register): %d\n",
			err);
		goto get_maskset_unlock;
	} else if (err != 2) {
		dev_err(ab3100->dev,
			"write error (write register) "
			"%d bytes transferred (expected 2)\n",
			err);
		err = -EIO;
		goto get_maskset_unlock;
	}

	/* All is well */
	err = 0;

 get_maskset_unlock:
	mutex_unlock(&ab3100->access_mutex);
	return err;
}