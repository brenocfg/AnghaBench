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
struct resource {int dummy; } ;
struct omap_hwmod {int dummy; } ;
struct omap_device {int hwmods_cnt; struct omap_hwmod** hwmods; } ;

/* Variables and functions */
 int omap_hwmod_fill_resources (struct omap_hwmod*,struct resource*) ; 

int omap_device_fill_resources(struct omap_device *od, struct resource *res)
{
	struct omap_hwmod *oh;
	int c = 0;
	int i, r;

	for (i = 0, oh = *od->hwmods; i < od->hwmods_cnt; i++, oh++) {
		r = omap_hwmod_fill_resources(oh, res);
		res += r;
		c += r;
	}

	return 0;
}