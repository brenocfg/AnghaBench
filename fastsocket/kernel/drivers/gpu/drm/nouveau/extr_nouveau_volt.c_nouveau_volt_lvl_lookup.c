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
struct nouveau_pm_voltage {int nr_level; TYPE_1__* level; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {struct nouveau_pm_voltage voltage; } ;
struct TYPE_3__ {int vid; int voltage; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_2__* nouveau_pm (struct drm_device*) ; 

int
nouveau_volt_lvl_lookup(struct drm_device *dev, int vid)
{
	struct nouveau_pm_voltage *volt = &nouveau_pm(dev)->voltage;
	int i;

	for (i = 0; i < volt->nr_level; i++) {
		if (volt->level[i].vid == vid)
			return volt->level[i].voltage;
	}

	return -ENOENT;
}