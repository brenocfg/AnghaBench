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
struct push_switch_platform_info {char* name; } ;
struct device_attribute {int dummy; } ;
struct device {struct push_switch_platform_info* platform_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t switch_show(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	struct push_switch_platform_info *psw_info = dev->platform_data;
	return sprintf(buf, "%s\n", psw_info->name);
}