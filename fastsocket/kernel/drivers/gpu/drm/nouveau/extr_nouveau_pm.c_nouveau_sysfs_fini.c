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
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_1__ attr; } ;
struct nouveau_pm_level {TYPE_3__ dev_attr; } ;
struct nouveau_pm {int nr_perflvl; struct nouveau_pm_level* perflvl; } ;
struct drm_device {TYPE_2__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 TYPE_3__ dev_attr_performance_level ; 
 int /*<<< orphan*/  device_remove_file (struct device*,TYPE_3__*) ; 
 struct nouveau_pm* nouveau_pm (struct drm_device*) ; 

__attribute__((used)) static void
nouveau_sysfs_fini(struct drm_device *dev)
{
	struct nouveau_pm *pm = nouveau_pm(dev);
	struct device *d = &dev->pdev->dev;
	int i;

	device_remove_file(d, &dev_attr_performance_level);
	for (i = 0; i < pm->nr_perflvl; i++) {
		struct nouveau_pm_level *pl = &pm->perflvl[i];

		if (!pl->dev_attr.attr.name)
			break;

		device_remove_file(d, &pl->dev_attr);
	}
}