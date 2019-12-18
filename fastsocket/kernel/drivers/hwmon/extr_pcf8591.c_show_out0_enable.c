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
struct pcf8591_data {int control; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int PCF8591_CONTROL_AOEF ; 
 struct pcf8591_data* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t show_out0_enable(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct pcf8591_data *data = i2c_get_clientdata(to_i2c_client(dev));
	return sprintf(buf, "%u\n", !(!(data->control & PCF8591_CONTROL_AOEF)));
}