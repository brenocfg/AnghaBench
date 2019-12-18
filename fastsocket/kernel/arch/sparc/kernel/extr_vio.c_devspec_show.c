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
struct vio_dev {int /*<<< orphan*/  type; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 

__attribute__((used)) static ssize_t devspec_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct vio_dev *vdev = to_vio_dev(dev);
	const char *str = "none";

	if (!strcmp(vdev->type, "vnet-port"))
		str = "vnet";
	else if (!strcmp(vdev->type, "vdc-port"))
		str = "vdisk";

	return sprintf(buf, "%s\n", str);
}