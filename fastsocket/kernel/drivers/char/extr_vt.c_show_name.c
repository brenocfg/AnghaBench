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
struct con_driver {int flag; char* desc; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int CON_DRIVER_FLAG_MODULE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct con_driver* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static ssize_t show_name(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct con_driver *con = dev_get_drvdata(dev);

	return snprintf(buf, PAGE_SIZE, "%s %s\n",
			(con->flag & CON_DRIVER_FLAG_MODULE) ? "(M)" : "(S)",
			 con->desc);

}