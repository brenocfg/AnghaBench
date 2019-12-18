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
struct dock_station {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {scalar_t__ platform_data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_NOTIFY_EJECT_REQUEST ; 
 int EINVAL ; 
 int /*<<< orphan*/  begin_undock (struct dock_station*) ; 
 int handle_eject_request (struct dock_station*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t write_undock(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	int ret;
	struct dock_station *dock_station = *((struct dock_station **)
		dev->platform_data);

	if (!count)
		return -EINVAL;

	begin_undock(dock_station);
	ret = handle_eject_request(dock_station, ACPI_NOTIFY_EJECT_REQUEST);
	return ret ? ret: count;
}