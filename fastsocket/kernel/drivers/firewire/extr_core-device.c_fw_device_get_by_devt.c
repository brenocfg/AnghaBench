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
struct fw_device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_device_get (struct fw_device*) ; 
 int /*<<< orphan*/  fw_device_idr ; 
 int /*<<< orphan*/  fw_device_rwsem ; 
 struct fw_device* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct fw_device *fw_device_get_by_devt(dev_t devt)
{
	struct fw_device *device;

	down_read(&fw_device_rwsem);
	device = idr_find(&fw_device_idr, MINOR(devt));
	if (device)
		fw_device_get(device);
	up_read(&fw_device_rwsem);

	return device;
}