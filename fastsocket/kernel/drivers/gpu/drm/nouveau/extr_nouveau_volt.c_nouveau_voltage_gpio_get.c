#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct nouveau_pm_voltage {int vid_mask; } ;
struct nouveau_gpio {int (* get ) (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct nouveau_pm_voltage voltage; } ;

/* Variables and functions */
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_gpio* nouveau_gpio (struct nouveau_device*) ; 
 TYPE_1__* nouveau_pm (struct drm_device*) ; 
 int nouveau_volt_lvl_lookup (struct drm_device*,int) ; 
 int nr_vidtag ; 
 int stub1 (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vidtag ; 

int
nouveau_voltage_gpio_get(struct drm_device *dev)
{
	struct nouveau_pm_voltage *volt = &nouveau_pm(dev)->voltage;
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_gpio *gpio = nouveau_gpio(device);
	u8 vid = 0;
	int i;

	for (i = 0; i < nr_vidtag; i++) {
		if (!(volt->vid_mask & (1 << i)))
			continue;

		vid |= gpio->get(gpio, 0, vidtag[i], 0xff) << i;
	}

	return nouveau_volt_lvl_lookup(dev, vid);
}