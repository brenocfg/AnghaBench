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
struct qib_devdata {int /*<<< orphan*/  eep_lock; int /*<<< orphan*/  twsi_eeprom_dev; } ;

/* Variables and functions */
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int qib_twsi_blk_rd (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int qib_twsi_reset (struct qib_devdata*) ; 

int qib_eeprom_read(struct qib_devdata *dd, u8 eeprom_offset,
		    void *buff, int len)
{
	int ret;

	ret = mutex_lock_interruptible(&dd->eep_lock);
	if (!ret) {
		ret = qib_twsi_reset(dd);
		if (ret)
			qib_dev_err(dd, "EEPROM Reset for read failed\n");
		else
			ret = qib_twsi_blk_rd(dd, dd->twsi_eeprom_dev,
					      eeprom_offset, buff, len);
		mutex_unlock(&dd->eep_lock);
	}

	return ret;
}