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
typedef  int /*<<< orphan*/  u32 ;
struct nv04_pm_clock {int /*<<< orphan*/  calc; int /*<<< orphan*/  pll; } ;
struct nouveau_device {int dummy; } ;
struct nouveau_clock {int (* pll_calc ) (struct nouveau_clock*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;} ;
struct nouveau_bios {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_device*) ; 
 struct nouveau_clock* nouveau_clock (struct nouveau_device*) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 int nvbios_pll_parse (struct nouveau_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct nouveau_clock*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
calc_pll(struct drm_device *dev, u32 id, int khz, struct nv04_pm_clock *clk)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_bios *bios = nouveau_bios(device);
	struct nouveau_clock *pclk = nouveau_clock(device);
	int ret;

	ret = nvbios_pll_parse(bios, id, &clk->pll);
	if (ret)
		return ret;

	ret = pclk->pll_calc(pclk, &clk->pll, khz, &clk->calc);
	if (!ret)
		return -EINVAL;

	return 0;
}