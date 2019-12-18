#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct max1363_state {TYPE_1__* chip_info; } ;
struct iio_dev {struct max1363_state* dev_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {int num_modes; size_t* mode_list; } ;

/* Variables and functions */
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 TYPE_2__* max1363_mode_table ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t max1363_show_av_scan_modes(struct device *dev,
					  struct device_attribute *attr,
					  char *buf)
{
	struct iio_dev *dev_info = dev_get_drvdata(dev);
	struct max1363_state *st = dev_info->dev_data;
	int i, len = 0;

	for (i = 0; i < st->chip_info->num_modes; i++)
		len += sprintf(buf + len, "%s ",
			       max1363_mode_table[st->chip_info
						  ->mode_list[i]].name);
	len += sprintf(buf + len, "\n");

	return len;
}