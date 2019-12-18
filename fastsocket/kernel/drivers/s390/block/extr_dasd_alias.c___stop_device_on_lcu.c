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
struct dasd_device {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STOPPED_SU ; 
 int /*<<< orphan*/  dasd_device_set_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __stop_device_on_lcu(struct dasd_device *device,
				 struct dasd_device *pos)
{
	/* If pos == device then device is already locked! */
	if (pos == device) {
		dasd_device_set_stop_bits(pos, DASD_STOPPED_SU);
		return;
	}
	spin_lock(get_ccwdev_lock(pos->cdev));
	dasd_device_set_stop_bits(pos, DASD_STOPPED_SU);
	spin_unlock(get_ccwdev_lock(pos->cdev));
}