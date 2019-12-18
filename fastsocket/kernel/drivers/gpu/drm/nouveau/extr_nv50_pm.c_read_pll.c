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
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_src_dom6 ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int read_clk (struct drm_device*,int /*<<< orphan*/ ) ; 
 int read_pll_ref (struct drm_device*,int) ; 

__attribute__((used)) static u32
read_pll(struct drm_device *dev, u32 base)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_drm *drm = nouveau_drm(dev);
	u32 mast = nv_rd32(device, 0x00c040);
	u32 ctrl = nv_rd32(device, base + 0);
	u32 coef = nv_rd32(device, base + 4);
	u32 ref = read_pll_ref(dev, base);
	u32 clk = 0;
	int N1, N2, M1, M2;

	if (base == 0x004028 && (mast & 0x00100000)) {
		/* wtf, appears to only disable post-divider on nva0 */
		if (nv_device(drm->device)->chipset != 0xa0)
			return read_clk(dev, clk_src_dom6);
	}

	N2 = (coef & 0xff000000) >> 24;
	M2 = (coef & 0x00ff0000) >> 16;
	N1 = (coef & 0x0000ff00) >> 8;
	M1 = (coef & 0x000000ff);
	if ((ctrl & 0x80000000) && M1) {
		clk = ref * N1 / M1;
		if ((ctrl & 0x40000100) == 0x40000000) {
			if (M2)
				clk = clk * N2 / M2;
			else
				clk = 0;
		}
	}

	return clk;
}