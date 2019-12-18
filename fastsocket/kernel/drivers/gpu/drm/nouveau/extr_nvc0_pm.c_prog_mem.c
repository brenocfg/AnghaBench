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
struct nvc0_pm_state {int /*<<< orphan*/  perflvl; } ;
struct nouveau_mem_exec_func {struct nvc0_pm_state* priv; int /*<<< orphan*/  timing_set; int /*<<< orphan*/  clock_set; int /*<<< orphan*/  mrs; int /*<<< orphan*/  mrg; int /*<<< orphan*/  wait; int /*<<< orphan*/  refresh_self; int /*<<< orphan*/  refresh_auto; int /*<<< orphan*/  refresh; int /*<<< orphan*/  precharge; struct drm_device* dev; } ;
struct nouveau_device {int chipset; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  nouveau_mem_exec (struct nouveau_mem_exec_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int,int) ; 

__attribute__((used)) static void
prog_mem(struct drm_device *dev, struct nvc0_pm_state *info)
{
	struct nouveau_device *device = nouveau_dev(dev);
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

	if (device->chipset < 0xd0)
		nv_wr32(device, 0x611200, 0x00003300);
	else
		nv_wr32(device, 0x62c000, 0x03030000);

	nouveau_mem_exec(&exec, info->perflvl);

	if (device->chipset < 0xd0)
		nv_wr32(device, 0x611200, 0x00003330);
	else
		nv_wr32(device, 0x62c000, 0x03030300);
}