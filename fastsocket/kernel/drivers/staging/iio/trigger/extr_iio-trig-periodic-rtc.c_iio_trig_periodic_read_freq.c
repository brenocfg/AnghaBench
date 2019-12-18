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
struct iio_trigger {struct iio_prtc_trigger_info* private_data; } ;
struct iio_prtc_trigger_info {int frequency; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct iio_trigger* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t iio_trig_periodic_read_freq(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct iio_trigger *trig = dev_get_drvdata(dev);
	struct iio_prtc_trigger_info *trig_info = trig->private_data;
	return sprintf(buf, "%u\n", trig_info->frequency);
}