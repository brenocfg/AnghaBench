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
struct nouveau_pm_voltage {int /*<<< orphan*/  level; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct nouveau_pm_voltage voltage; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 TYPE_1__* nouveau_pm (struct drm_device*) ; 

void
nouveau_volt_fini(struct drm_device *dev)
{
	struct nouveau_pm_voltage *volt = &nouveau_pm(dev)->voltage;

	kfree(volt->level);
}