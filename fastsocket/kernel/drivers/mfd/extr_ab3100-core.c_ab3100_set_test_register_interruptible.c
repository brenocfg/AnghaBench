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
struct ab3100 {int /*<<< orphan*/  access_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  testreg_client; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ab3100_set_test_register_interruptible(struct ab3100 *ab3100,
				    u8 reg, u8 regval)
{
	u8 regandval[2] = {reg, regval};
	int err;

	err = mutex_lock_interruptible(&ab3100->access_mutex);
	if (err)
		return err;

	err = i2c_master_send(ab3100->testreg_client, regandval, 2);
	if (err < 0) {
		dev_err(ab3100->dev,
			"write error (write test register): %d\n",
			err);
	} else if (err != 2) {
		dev_err(ab3100->dev,
			"write error (write test register) "
			"%d bytes transferred (expected 2)\n",
			err);
		err = -EIO;
	} else {
		/* All is well */
		err = 0;
	}
	mutex_unlock(&ab3100->access_mutex);

	return err;
}