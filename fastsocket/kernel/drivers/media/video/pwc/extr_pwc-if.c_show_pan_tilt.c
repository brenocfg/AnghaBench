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
struct pwc_device {int pan_angle; int tilt_angle; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct pwc_device* cd_to_pwc (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t show_pan_tilt(struct device *class_dev,
			     struct device_attribute *attr, char *buf)
{
	struct pwc_device *pdev = cd_to_pwc(class_dev);
	return sprintf(buf, "%d %d\n", pdev->pan_angle, pdev->tilt_angle);
}