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
struct of_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int of_device_get_modalias (struct of_device*,char*,scalar_t__) ; 
 struct of_device* to_of_device (struct device*) ; 

__attribute__((used)) static ssize_t modalias_show (struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	struct of_device *ofdev = to_of_device(dev);
	int len;

	len = of_device_get_modalias(ofdev, buf, PAGE_SIZE - 2);

	buf[len] = '\n';
	buf[len+1] = 0;

	return len+1;
}