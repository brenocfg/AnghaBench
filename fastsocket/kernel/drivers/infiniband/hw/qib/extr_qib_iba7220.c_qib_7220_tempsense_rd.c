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
typedef  int u8 ;
struct qib_devdata {int /*<<< orphan*/  eep_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QIB_TWSI_TEMP_DEV ; 
 int VALID_TS_RD_REG_MASK ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qib_twsi_blk_rd (struct qib_devdata*,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int qib_7220_tempsense_rd(struct qib_devdata *dd, int regnum)
{
	int ret;
	u8 rdata;

	if (regnum > 7) {
		ret = -EINVAL;
		goto bail;
	}

	/* return a bogus value for (the one) register we do not have */
	if (!((1 << regnum) & VALID_TS_RD_REG_MASK)) {
		ret = 0;
		goto bail;
	}

	ret = mutex_lock_interruptible(&dd->eep_lock);
	if (ret)
		goto bail;

	ret = qib_twsi_blk_rd(dd, QIB_TWSI_TEMP_DEV, regnum, &rdata, 1);
	if (!ret)
		ret = rdata;

	mutex_unlock(&dd->eep_lock);

	/*
	 * There are three possibilities here:
	 * ret is actual value (0..255)
	 * ret is -ENXIO or -EINVAL from twsi code or this file
	 * ret is -EINTR from mutex_lock_interruptible.
	 */
bail:
	return ret;
}