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
struct max6650_data {int speed; int /*<<< orphan*/  config; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 int clock ; 
 struct max6650_data* max6650_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t get_target(struct device *dev, struct device_attribute *devattr,
			 char *buf)
{
	struct max6650_data *data = max6650_update_device(dev);
	int kscale, ktach, rpm;

	/*
	* Use the datasheet equation:
	*
	*    FanSpeed = KSCALE x fCLK / [256 x (KTACH + 1)]
	*
	* then multiply by 60 to give rpm.
	*/

	kscale = DIV_FROM_REG(data->config);
	ktach = data->speed;
	rpm = 60 * kscale * clock / (256 * (ktach + 1));
	return sprintf(buf, "%d\n", rpm);
}