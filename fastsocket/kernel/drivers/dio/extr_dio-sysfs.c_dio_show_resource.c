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
struct dio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ dio_resource_end (struct dio_dev*) ; 
 int /*<<< orphan*/  dio_resource_flags (struct dio_dev*) ; 
 scalar_t__ dio_resource_start (struct dio_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 struct dio_dev* to_dio_dev (struct device*) ; 

__attribute__((used)) static ssize_t dio_show_resource(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct dio_dev *d = to_dio_dev(dev);

	return sprintf(buf, "0x%08lx 0x%08lx 0x%08lx\n",
		       (unsigned long)dio_resource_start(d),
		       (unsigned long)dio_resource_end(d),
		       dio_resource_flags(d));
}