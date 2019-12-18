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
struct nouveau_pm_level {void* core; void* copy; void* daemon; void* vdec; void* unka0; void* memory; void* shader; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 void* read_clk (struct drm_device*,int,int) ; 
 void* read_pll (struct drm_device*,int,int) ; 

int
nva3_pm_clocks_get(struct drm_device *dev, struct nouveau_pm_level *perflvl)
{
	perflvl->core   = read_pll(dev, 0x00, 0x4200);
	perflvl->shader = read_pll(dev, 0x01, 0x4220);
	perflvl->memory = read_pll(dev, 0x02, 0x4000);
	perflvl->unka0  = read_clk(dev, 0x20, false);
	perflvl->vdec   = read_clk(dev, 0x21, false);
	perflvl->daemon = read_clk(dev, 0x25, false);
	perflvl->copy   = perflvl->core;
	return 0;
}