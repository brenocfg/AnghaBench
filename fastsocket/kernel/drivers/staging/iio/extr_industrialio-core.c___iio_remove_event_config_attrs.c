#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct iio_dev {TYPE_3__* event_attrs; TYPE_2__ dev; TYPE_1__* event_conf_attrs; } ;
struct attribute {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {struct attribute** attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_remove_file_from_group (int /*<<< orphan*/ *,struct attribute*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __iio_remove_event_config_attrs(struct iio_dev *dev_info,
						  int i)
{
	struct attribute **attrq;

	if (dev_info->event_conf_attrs
		&& dev_info->event_conf_attrs[i].attrs) {
		attrq = dev_info->event_conf_attrs[i].attrs;
		while (*attrq) {
			sysfs_remove_file_from_group(&dev_info->dev.kobj,
						     *attrq,
						     dev_info
						     ->event_attrs[i].name);
			attrq++;
		}
	}

	return 0;
}