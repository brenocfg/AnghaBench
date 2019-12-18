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
struct lcd_device {int /*<<< orphan*/  ops_lock; TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_contrast ) (struct lcd_device*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct lcd_device*,int) ; 
 struct lcd_device* to_lcd_device (struct device*) ; 

__attribute__((used)) static ssize_t lcd_store_contrast(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int rc = -ENXIO;
	char *endp;
	struct lcd_device *ld = to_lcd_device(dev);
	int contrast = simple_strtoul(buf, &endp, 0);
	size_t size = endp - buf;

	if (isspace(*endp))
		size++;
	if (size != count)
		return -EINVAL;

	mutex_lock(&ld->ops_lock);
	if (ld->ops && ld->ops->set_contrast) {
		pr_debug("lcd: set contrast to %d\n", contrast);
		ld->ops->set_contrast(ld, contrast);
		rc = count;
	}
	mutex_unlock(&ld->ops_lock);

	return rc;
}