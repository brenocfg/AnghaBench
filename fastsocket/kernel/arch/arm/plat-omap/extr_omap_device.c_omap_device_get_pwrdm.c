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
struct powerdomain {int dummy; } ;
struct omap_device {int /*<<< orphan*/ * hwmods; int /*<<< orphan*/  hwmods_cnt; } ;

/* Variables and functions */
 struct powerdomain* omap_hwmod_get_pwrdm (int /*<<< orphan*/ ) ; 

struct powerdomain *omap_device_get_pwrdm(struct omap_device *od)
{
	/*
	 * XXX Assumes that all omap_hwmod powerdomains are identical.
	 * This may not necessarily be true.  There should be a sanity
	 * check in here to WARN() if any difference appears.
	 */
	if (!od->hwmods_cnt)
		return NULL;

	return omap_hwmod_get_pwrdm(od->hwmods[0]);
}