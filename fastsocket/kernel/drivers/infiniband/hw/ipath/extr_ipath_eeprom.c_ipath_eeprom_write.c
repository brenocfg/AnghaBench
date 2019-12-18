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
struct ipath_devdata {int /*<<< orphan*/  ipath_eep_lock; } ;

/* Variables and functions */
 int ipath_eeprom_internal_write (struct ipath_devdata*,int /*<<< orphan*/ ,void const*,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ipath_eeprom_write(struct ipath_devdata *dd, u8 eeprom_offset,
			const void *buff, int len)
{
	int ret;

	ret = mutex_lock_interruptible(&dd->ipath_eep_lock);
	if (!ret) {
		ret = ipath_eeprom_internal_write(dd, eeprom_offset, buff, len);
		mutex_unlock(&dd->ipath_eep_lock);
	}

	return ret;
}