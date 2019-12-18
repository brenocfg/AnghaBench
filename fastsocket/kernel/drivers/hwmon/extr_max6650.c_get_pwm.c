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
struct max6650_data {int config; scalar_t__ dac; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int MAX6650_CFG_V12 ; 
 struct max6650_data* max6650_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t get_pwm(struct device *dev, struct device_attribute *devattr,
		       char *buf)
{
	int pwm;
	struct max6650_data *data = max6650_update_device(dev);

	/* Useful range for dac is 0-180 for 12V fans and 0-76 for 5V fans.
	   Lower DAC values mean higher speeds. */
	if (data->config & MAX6650_CFG_V12)
		pwm = 255 - (255 * (int)data->dac)/180;
	else
		pwm = 255 - (255 * (int)data->dac)/76;

	if (pwm < 0)
		pwm = 0;

	return sprintf(buf, "%d\n", pwm);
}