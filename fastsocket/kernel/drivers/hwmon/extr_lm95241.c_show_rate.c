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
struct lm95241_data {int rate; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ PAGE_SIZE ; 
 struct lm95241_data* lm95241_update_device (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t show_rate(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct lm95241_data *data = lm95241_update_device(dev);

	snprintf(buf, PAGE_SIZE - 1, "%lu\n", 1000 * data->rate / HZ);
	return strlen(buf);
}