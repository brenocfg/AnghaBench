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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int device_schedule_callback (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_store_delete_callback ; 

__attribute__((used)) static ssize_t
sdev_store_delete(struct device *dev, struct device_attribute *attr,
		  const char *buf, size_t count)
{
	int rc;

	/* An attribute cannot be unregistered by one of its own methods,
	 * so we have to use this roundabout approach.
	 */
	rc = device_schedule_callback(dev, sdev_store_delete_callback);
	if (rc)
		count = rc;
	return count;
}