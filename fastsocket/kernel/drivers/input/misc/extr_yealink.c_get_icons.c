#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct yealink_dev {char* lcdMap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_5__ {char* name; } ;
struct TYPE_6__ {TYPE_1__ p; } ;
struct TYPE_7__ {char type; TYPE_2__ u; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int ENODEV ; 
 struct yealink_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 TYPE_3__* lcdMap ; 
 scalar_t__ sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  sysfs_rwsema ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t get_icons(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct yealink_dev *yld;
	int i, ret = 1;

	down_read(&sysfs_rwsema);
	yld = dev_get_drvdata(dev);
	if (yld == NULL) {
		up_read(&sysfs_rwsema);
		return -ENODEV;
	}

	for (i = 0; i < ARRAY_SIZE(lcdMap); i++) {
		if (lcdMap[i].type != '.')
			continue;
		ret += sprintf(&buf[ret], "%s %s\n",
				yld->lcdMap[i] == ' ' ? "  " : "on",
				lcdMap[i].u.p.name);
	}
	up_read(&sysfs_rwsema);
	return ret;
}