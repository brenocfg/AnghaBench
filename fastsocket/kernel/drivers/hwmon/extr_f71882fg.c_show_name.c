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
struct f71882fg_data {size_t type; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct f71882fg_data* dev_get_drvdata (struct device*) ; 
 char** f71882fg_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t show_name(struct device *dev, struct device_attribute *devattr,
	char *buf)
{
	struct f71882fg_data *data = dev_get_drvdata(dev);
	return sprintf(buf, "%s\n", f71882fg_names[data->type]);
}