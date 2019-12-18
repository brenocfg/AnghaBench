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
struct omap_hwmod {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct omap_device {int hwmods_cnt; TYPE_1__ pdev; struct omap_hwmod** hwmods; } ;

/* Variables and functions */
 scalar_t__ omap_hwmod_count_resources (struct omap_hwmod*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int) ; 

int omap_device_count_resources(struct omap_device *od)
{
	struct omap_hwmod *oh;
	int c = 0;
	int i;

	for (i = 0, oh = *od->hwmods; i < od->hwmods_cnt; i++, oh++)
		c += omap_hwmod_count_resources(oh);

	pr_debug("omap_device: %s: counted %d total resources across %d "
		 "hwmods\n", od->pdev.name, c, od->hwmods_cnt);

	return c;
}