#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tg3 {TYPE_2__* pdev; int /*<<< orphan*/ * hwmon_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_group ; 

__attribute__((used)) static void tg3_hwmon_close(struct tg3 *tp)
{
	if (tp->hwmon_dev) {
		hwmon_device_unregister(tp->hwmon_dev);
		tp->hwmon_dev = NULL;
		sysfs_remove_group(&tp->pdev->dev.kobj, &tg3_group);
	}
}