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
struct viodasd_device {int /*<<< orphan*/ * disk; } ;
struct device_driver {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t MAX_DISKNO ; 
 int /*<<< orphan*/  probe_disk (struct viodasd_device*) ; 
 struct viodasd_device* viodasd_devices ; 

__attribute__((used)) static ssize_t probe_disks(struct device_driver *drv, const char *buf,
		size_t count)
{
	struct viodasd_device *d;

	for (d = viodasd_devices; d < &viodasd_devices[MAX_DISKNO]; d++) {
		if (d->disk == NULL)
			probe_disk(d);
	}
	return count;
}