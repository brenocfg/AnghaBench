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
struct omap_hwmod {int dummy; } ;
struct omap_device {int hwmods_cnt; struct omap_hwmod** hwmods; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_hwmod_idle (struct omap_hwmod*) ; 

int omap_device_idle_hwmods(struct omap_device *od)
{
	struct omap_hwmod *oh;
	int i;

	for (i = 0, oh = *od->hwmods; i < od->hwmods_cnt; i++, oh++)
		omap_hwmod_idle(oh);

	/* XXX pass along return value here? */
	return 0;
}