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
struct yealink_dev {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ p; } ;
struct TYPE_7__ {char type; TYPE_2__ u; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 size_t ENODEV ; 
 struct yealink_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 TYPE_3__* lcdMap ; 
 int /*<<< orphan*/  setChar (struct yealink_dev*,int,int) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sysfs_rwsema ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t set_icon(struct device *dev, const char *buf, size_t count,
			int chr)
{
	struct yealink_dev *yld;
	int i;

	down_write(&sysfs_rwsema);
	yld = dev_get_drvdata(dev);
	if (yld == NULL) {
		up_write(&sysfs_rwsema);
		return -ENODEV;
	}

	for (i = 0; i < ARRAY_SIZE(lcdMap); i++) {
		if (lcdMap[i].type != '.')
			continue;
		if (strncmp(buf, lcdMap[i].u.p.name, count) == 0) {
			setChar(yld, i, chr);
			break;
		}
	}

	up_write(&sysfs_rwsema);
	return count;
}