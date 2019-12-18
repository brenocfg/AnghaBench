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
struct pwc_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct pwc_device* cd_to_pwc (struct device*) ; 
 int pwc_mpt_reset (struct pwc_device*,int) ; 
 int pwc_mpt_set_angle (struct pwc_device*,int,int) ; 
 scalar_t__ sscanf (char const*,char*,int*,int*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static ssize_t store_pan_tilt(struct device *class_dev,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct pwc_device *pdev = cd_to_pwc(class_dev);
	int pan, tilt;
	int ret = -EINVAL;

	if (strncmp(buf, "reset", 5) == 0)
		ret = pwc_mpt_reset(pdev, 0x3);

	else if (sscanf(buf, "%d %d", &pan, &tilt) > 0)
		ret = pwc_mpt_set_angle(pdev, pan, tilt);

	if (ret < 0)
		return ret;
	return strlen(buf);
}