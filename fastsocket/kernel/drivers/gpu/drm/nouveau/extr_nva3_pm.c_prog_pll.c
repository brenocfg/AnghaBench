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
typedef  int u32 ;
struct nouveau_drm {int dummy; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct creg {int clk; int /*<<< orphan*/  pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_device*,int const,int,int) ; 
 int /*<<< orphan*/  nv_wait (struct nouveau_device*,int const,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
prog_pll(struct drm_device *dev, int clk, u32 pll, struct creg *reg)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_drm *drm = nouveau_drm(dev);
	const u32 src0 = 0x004120 + (clk * 4);
	const u32 src1 = 0x004160 + (clk * 4);
	const u32 ctrl = pll + 0;
	const u32 coef = pll + 4;

	if (!reg->clk && !reg->pll) {
		NV_DEBUG(drm, "no clock for %02x\n", clk);
		return;
	}

	if (reg->pll) {
		nv_mask(device, src0, 0x00000101, 0x00000101);
		nv_wr32(device, coef, reg->pll);
		nv_mask(device, ctrl, 0x00000015, 0x00000015);
		nv_mask(device, ctrl, 0x00000010, 0x00000000);
		nv_wait(device, ctrl, 0x00020000, 0x00020000);
		nv_mask(device, ctrl, 0x00000010, 0x00000010);
		nv_mask(device, ctrl, 0x00000008, 0x00000000);
		nv_mask(device, src1, 0x00000100, 0x00000000);
		nv_mask(device, src1, 0x00000001, 0x00000000);
	} else {
		nv_mask(device, src1, 0x003f3141, 0x00000101 | reg->clk);
		nv_mask(device, ctrl, 0x00000018, 0x00000018);
		udelay(20);
		nv_mask(device, ctrl, 0x00000001, 0x00000000);
		nv_mask(device, src0, 0x00000100, 0x00000000);
		nv_mask(device, src0, 0x00000001, 0x00000000);
	}
}