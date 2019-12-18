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
struct iio_dev {TYPE_1__* trig; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_TRIGGER_NAME_LENGTH ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t iio_trigger_read_current(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct iio_dev *dev_info = dev_get_drvdata(dev);
	int len = 0;
	if (dev_info->trig)
		len = snprintf(buf,
			       IIO_TRIGGER_NAME_LENGTH,
			       "%s\n",
			       dev_info->trig->name);
	return len;
}