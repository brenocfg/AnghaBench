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
struct dock_station {int flags; } ;
struct device_attribute {int dummy; } ;
struct device {scalar_t__ platform_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int DOCK_IS_ATA ; 
 int DOCK_IS_BAT ; 
 int DOCK_IS_DOCK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t show_dock_type(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct dock_station *dock_station = *((struct dock_station **)
		dev->platform_data);
	char *type;

	if (dock_station->flags & DOCK_IS_DOCK)
		type = "dock_station";
	else if (dock_station->flags & DOCK_IS_ATA)
		type = "ata_bay";
	else if (dock_station->flags & DOCK_IS_BAT)
		type = "battery_bay";
	else
		type = "unknown";

	return snprintf(buf, PAGE_SIZE, "%s\n", type);
}