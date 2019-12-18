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
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_contrast ) (struct display_device*,int) ;} ;

/* Variables and functions */
 size_t EINVAL ; 
 struct display_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct display_device*,int) ; 

__attribute__((used)) static ssize_t display_store_contrast(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct display_device *dsp = dev_get_drvdata(dev);
	ssize_t ret = -EINVAL, size;
	int contrast;
	char *endp;

	contrast = simple_strtoul(buf, &endp, 0);
	size = endp - buf;

	if (isspace(*endp))
		size++;

	if (size != count)
		return ret;

	mutex_lock(&dsp->lock);
	if (likely(dsp->driver && dsp->driver->set_contrast)) {
		pr_debug("display: set contrast to %d\n", contrast);
		dsp->driver->set_contrast(dsp, contrast);
		ret = count;
	}
	mutex_unlock(&dsp->lock);
	return ret;
}