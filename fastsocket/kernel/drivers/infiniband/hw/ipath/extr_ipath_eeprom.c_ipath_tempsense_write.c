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
struct ipath_devdata {int /*<<< orphan*/  ipath_eep_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int VALID_TS_WR_REG_MASK ; 
 int ipath_tempsense_internal_write (struct ipath_devdata*,int,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ipath_tempsense_write(struct ipath_devdata *dd, u8 regnum, u8 data)
{
	int ret;

	if (regnum > 15 || !((1 << regnum) & VALID_TS_WR_REG_MASK))
		return -EINVAL;

	ret = mutex_lock_interruptible(&dd->ipath_eep_lock);
	if (!ret) {
		ret = ipath_tempsense_internal_write(dd, regnum, data);
		mutex_unlock(&dd->ipath_eep_lock);
	}

	/*
	 * There are three possibilities here:
	 * ret is 0 for success
	 * ret is -ENXIO or -EINVAL from code in this file
	 * ret is -EINTR from mutex_lock_interruptible.
	 */
	return ret;
}