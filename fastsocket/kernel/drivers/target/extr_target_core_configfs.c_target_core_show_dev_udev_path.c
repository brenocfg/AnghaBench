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
struct se_device {int dev_flags; char* udev_path; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int DF_USING_UDEV_PATH ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t target_core_show_dev_udev_path(void *p, char *page)
{
	struct se_device *dev = p;

	if (!(dev->dev_flags & DF_USING_UDEV_PATH))
		return 0;

	return snprintf(page, PAGE_SIZE, "%s\n", dev->udev_path);
}