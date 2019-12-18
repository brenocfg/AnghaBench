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
struct nvbios_pll {int bias_p; } ;
struct hwsq_ucode {int dummy; } ;
struct nv50_pm_state {int mctrl; int mcoef; struct hwsq_ucode mclk_hwsq; } ;
struct nouveau_pm_level {int /*<<< orphan*/  memory; } ;
struct nouveau_mem_exec_func {struct nv50_pm_state* priv; int /*<<< orphan*/  timing_set; int /*<<< orphan*/  clock_set; int /*<<< orphan*/  mrs; int /*<<< orphan*/  mrg; int /*<<< orphan*/  wait; int /*<<< orphan*/  refresh_self; int /*<<< orphan*/  refresh_auto; int /*<<< orphan*/  refresh; int /*<<< orphan*/  precharge; struct drm_device* dev; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 int EINVAL ; 
 int calc_pll (struct drm_device*,int,struct nvbios_pll*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 scalar_t__ clk_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_src_href ; 
 int /*<<< orphan*/  hwsq_fini (struct hwsq_ucode*) ; 
 int /*<<< orphan*/  hwsq_init (struct hwsq_ucode*) ; 
 int /*<<< orphan*/  hwsq_op5f (struct hwsq_ucode*,int,int) ; 
 int /*<<< orphan*/  hwsq_setf (struct hwsq_ucode*,int,int) ; 
 int /*<<< orphan*/  hwsq_wr32 (struct hwsq_ucode*,int,int) ; 
 int /*<<< orphan*/  mclk_clock_set ; 
 int /*<<< orphan*/  mclk_mrg ; 
 int /*<<< orphan*/  mclk_mrs ; 
 int /*<<< orphan*/  mclk_precharge ; 
 int /*<<< orphan*/  mclk_refresh ; 
 int /*<<< orphan*/  mclk_refresh_auto ; 
 int /*<<< orphan*/  mclk_refresh_self ; 
 int /*<<< orphan*/  mclk_timing_set ; 
 int /*<<< orphan*/  mclk_wait ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int nouveau_mem_exec (struct nouveau_mem_exec_func*,struct nouveau_pm_level*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int /*<<< orphan*/  read_clk (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
calc_mclk(struct drm_device *dev, struct nouveau_pm_level *perflvl,
	  struct nv50_pm_state *info)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_device *device = nouveau_dev(dev);
	u32 crtc_mask = 0; /*XXX: nv50_display_active_crtcs(dev); */
	struct nouveau_mem_exec_func exec = {
		.dev = dev,
		.precharge = mclk_precharge,
		.refresh = mclk_refresh,
		.refresh_auto = mclk_refresh_auto,
		.refresh_self = mclk_refresh_self,
		.wait = mclk_wait,
		.mrg = mclk_mrg,
		.mrs = mclk_mrs,
		.clock_set = mclk_clock_set,
		.timing_set = mclk_timing_set,
		.priv = info
	};
	struct hwsq_ucode *hwsq = &info->mclk_hwsq;
	struct nvbios_pll pll;
	int N, M, P;
	int ret;

	/* use pcie refclock if possible, otherwise use mpll */
	info->mctrl  = nv_rd32(device, 0x004008);
	info->mctrl &= ~0x81ff0200;
	if (clk_same(perflvl->memory, read_clk(dev, clk_src_href))) {
		info->mctrl |= 0x00000200 | (pll.bias_p << 19);
	} else {
		ret = calc_pll(dev, 0x4008, &pll, perflvl->memory, &N, &M, &P);
		if (ret == 0)
			return -EINVAL;

		info->mctrl |= 0x80000000 | (P << 22) | (P << 16);
		info->mctrl |= pll.bias_p << 19;
		info->mcoef  = (N << 8) | M;
	}

	/* build the ucode which will reclock the memory for us */
	hwsq_init(hwsq);
	if (crtc_mask) {
		hwsq_op5f(hwsq, crtc_mask, 0x00); /* wait for scanout */
		hwsq_op5f(hwsq, crtc_mask, 0x01); /* wait for vblank */
	}
	if (nv_device(drm->device)->chipset >= 0x92)
		hwsq_wr32(hwsq, 0x611200, 0x00003300); /* disable scanout */
	hwsq_setf(hwsq, 0x10, 0); /* disable bus access */
	hwsq_op5f(hwsq, 0x00, 0x01); /* no idea :s */

	ret = nouveau_mem_exec(&exec, perflvl);
	if (ret)
		return ret;

	hwsq_setf(hwsq, 0x10, 1); /* enable bus access */
	hwsq_op5f(hwsq, 0x00, 0x00); /* no idea, reverse of 0x00, 0x01? */
	if (nv_device(drm->device)->chipset >= 0x92)
		hwsq_wr32(hwsq, 0x611200, 0x00003330); /* enable scanout */
	hwsq_fini(hwsq);
	return 0;
}