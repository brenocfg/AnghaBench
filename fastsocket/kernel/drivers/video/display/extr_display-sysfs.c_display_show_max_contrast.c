#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct display_device {int /*<<< orphan*/  lock; TYPE_1__* driver; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int max_contrast; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 struct display_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ likely (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t display_show_max_contrast(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct display_device *dsp = dev_get_drvdata(dev);
	ssize_t rc = -ENXIO;

	mutex_lock(&dsp->lock);
	if (likely(dsp->driver))
		rc = sprintf(buf, "%d\n", dsp->driver->max_contrast);
	mutex_unlock(&dsp->lock);
	return rc;
}