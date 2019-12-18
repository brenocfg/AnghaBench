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
typedef  int ssize_t ;

/* Variables and functions */
 int isl1208_i2c_get_dtr (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t
isl1208_sysfs_show_dtrim(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	int dtr = isl1208_i2c_get_dtr(to_i2c_client(dev));
	if (dtr < 0)
		return dtr;

	return sprintf(buf, "%d ppm\n", dtr);
}