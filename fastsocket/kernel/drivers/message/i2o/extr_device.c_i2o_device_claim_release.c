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
struct TYPE_2__ {int /*<<< orphan*/  tid; } ;
struct i2o_device {int /*<<< orphan*/  lock; TYPE_1__ lct_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2O_CLAIM_PRIMARY ; 
 int /*<<< orphan*/  I2O_CMD_UTIL_RELEASE ; 
 int i2o_device_issue_claim (struct i2o_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ssleep (int) ; 

int i2o_device_claim_release(struct i2o_device *dev)
{
	int tries;
	int rc = 0;

	mutex_lock(&dev->lock);

	/*
	 *      If the controller takes a nonblocking approach to
	 *      releases we have to sleep/poll for a few times.
	 */
	for (tries = 0; tries < 10; tries++) {
		rc = i2o_device_issue_claim(dev, I2O_CMD_UTIL_RELEASE,
					    I2O_CLAIM_PRIMARY);
		if (!rc)
			break;

		ssleep(1);
	}

	if (!rc)
		pr_debug("i2o: claim release of device %d succeded\n",
			 dev->lct_data.tid);
	else
		pr_debug("i2o: claim release of device %d failed %d\n",
			 dev->lct_data.tid, rc);

	mutex_unlock(&dev->lock);

	return rc;
}