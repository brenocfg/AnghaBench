#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omapfb_device {TYPE_1__* panel; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int (* get_bklight_level ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct omapfb_device* dev_get_drvdata (struct device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (TYPE_1__*) ; 
 int stub2 (TYPE_1__*) ; 

__attribute__((used)) static ssize_t omapfb_show_bklight_level(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct omapfb_device *fbdev = dev_get_drvdata(dev);
	int r;

	if (fbdev->panel->get_bklight_level) {
		r = snprintf(buf, PAGE_SIZE, "%d\n",
			     fbdev->panel->get_bklight_level(fbdev->panel));
	} else
		r = -ENODEV;
	return r;
}