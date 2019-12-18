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
struct omap_device_pm_latency {int dummy; } ;
struct omap_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct omap_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct omap_device* omap_device_build_ss (char const*,int,struct omap_hwmod**,int,void*,int,struct omap_device_pm_latency*,int) ; 

struct omap_device *omap_device_build(const char *pdev_name, int pdev_id,
				      struct omap_hwmod *oh, void *pdata,
				      int pdata_len,
				      struct omap_device_pm_latency *pm_lats,
				      int pm_lats_cnt)
{
	struct omap_hwmod *ohs[] = { oh };

	if (!oh)
		return ERR_PTR(-EINVAL);

	return omap_device_build_ss(pdev_name, pdev_id, ohs, 1, pdata,
				    pdata_len, pm_lats, pm_lats_cnt);
}