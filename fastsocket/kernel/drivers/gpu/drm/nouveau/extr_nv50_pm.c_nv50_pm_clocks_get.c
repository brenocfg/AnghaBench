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
struct nouveau_pm_level {void* dom6; void* vdec; void* memory; void* shader; void* core; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_src_dom6 ; 
 int /*<<< orphan*/  clk_src_mclk ; 
 int /*<<< orphan*/  clk_src_nvclk ; 
 int /*<<< orphan*/  clk_src_sclk ; 
 int /*<<< orphan*/  clk_src_vdec ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 
 void* read_clk (struct drm_device*,int /*<<< orphan*/ ) ; 

int
nv50_pm_clocks_get(struct drm_device *dev, struct nouveau_pm_level *perflvl)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	if (nv_device(drm->device)->chipset == 0xaa ||
	    nv_device(drm->device)->chipset == 0xac)
		return 0;

	perflvl->core   = read_clk(dev, clk_src_nvclk);
	perflvl->shader = read_clk(dev, clk_src_sclk);
	perflvl->memory = read_clk(dev, clk_src_mclk);
	if (nv_device(drm->device)->chipset != 0x50) {
		perflvl->vdec = read_clk(dev, clk_src_vdec);
		perflvl->dom6 = read_clk(dev, clk_src_dom6);
	}

	return 0;
}