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
struct timed_output_dev {int (* get_time ) (struct timed_output_dev*) ;} ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct timed_output_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int stub1 (struct timed_output_dev*) ; 

__attribute__((used)) static ssize_t enable_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct timed_output_dev *tdev = dev_get_drvdata(dev);
	int remaining = tdev->get_time(tdev);

	return sprintf(buf, "%d\n", remaining);
}