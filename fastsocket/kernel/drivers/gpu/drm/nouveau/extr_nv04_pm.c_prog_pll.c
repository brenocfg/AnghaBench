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
typedef  int u32 ;
struct TYPE_2__ {int reg; } ;
struct nv04_pm_clock {int /*<<< orphan*/  calc; TYPE_1__ pll; } ;
struct nouveau_device {scalar_t__ card_type; } ;
struct nouveau_clock {int /*<<< orphan*/  (* pll_prog ) (struct nouveau_clock*,int,int /*<<< orphan*/ *) ;} ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NV_40 ; 
 struct nouveau_clock* nouveau_clock (struct nouveau_device*) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_clock*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prog_pll(struct drm_device *dev, struct nv04_pm_clock *clk)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_clock *pclk = nouveau_clock(device);
	u32 reg = clk->pll.reg;

	/* thank the insane nouveau_hw_setpll() interface for this */
	if (device->card_type >= NV_40)
		reg += 4;

	pclk->pll_prog(pclk, reg, &clk->calc);
}