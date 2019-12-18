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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7473_data {int max_duty_at_overheat; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct adt7473_data* adt7473_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_max_duty_at_crit(struct device *dev,
				     struct device_attribute *devattr,
				     char *buf)
{
	struct adt7473_data *data = adt7473_update_device(dev);
	return sprintf(buf, "%d\n", data->max_duty_at_overheat);
}