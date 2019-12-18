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
struct imon_context {int /*<<< orphan*/  lock; scalar_t__ display_isopen; int /*<<< orphan*/  display_supported; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct imon_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ssize_t show_imon_clock(struct device *d,
			       struct device_attribute *attr, char *buf)
{
	struct imon_context *ictx = dev_get_drvdata(d);
	size_t len;

	if (!ictx)
		return -ENODEV;

	mutex_lock(&ictx->lock);

	if (!ictx->display_supported) {
		len = snprintf(buf, PAGE_SIZE, "Not supported.");
	} else {
		len = snprintf(buf, PAGE_SIZE,
			"To set the clock on your iMON display:\n"
			"# date \"+%%y %%m %%d %%w %%H %%M %%S\" > imon_clock\n"
			"%s", ictx->display_isopen ?
			"\nNOTE: imon device must be closed\n" : "");
	}

	mutex_unlock(&ictx->lock);

	return len;
}