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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int gpio1; } ;
struct atxp1_data {TYPE_1__ reg; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ATXP1_GPIO1MASK ; 
 struct atxp1_data* atxp1_update_device (struct device*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t atxp1_showgpio1(struct device *dev, struct device_attribute *attr, char *buf)
{
	int size;
	struct atxp1_data *data;

	data = atxp1_update_device(dev);

	size = sprintf(buf, "0x%02x\n", data->reg.gpio1 & ATXP1_GPIO1MASK);

	return size;
}