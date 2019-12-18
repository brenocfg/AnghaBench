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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int) ; 
 int /*<<< orphan*/  clk_src_crystal ; 
 int /*<<< orphan*/  clk_src_href ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int read_clk (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
read_pll_src(struct drm_device *dev, u32 base)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_drm *drm = nouveau_drm(dev);
	u32 coef, ref = read_clk(dev, clk_src_crystal);
	u32 rsel = nv_rd32(device, 0x00e18c);
	int P, N, M, id;

	switch (nv_device(drm->device)->chipset) {
	case 0x50:
	case 0xa0:
		switch (base) {
		case 0x4020:
		case 0x4028: id = !!(rsel & 0x00000004); break;
		case 0x4008: id = !!(rsel & 0x00000008); break;
		case 0x4030: id = 0; break;
		default:
			NV_ERROR(drm, "ref: bad pll 0x%06x\n", base);
			return 0;
		}

		coef = nv_rd32(device, 0x00e81c + (id * 0x0c));
		ref *=  (coef & 0x01000000) ? 2 : 4;
		P    =  (coef & 0x00070000) >> 16;
		N    = ((coef & 0x0000ff00) >> 8) + 1;
		M    = ((coef & 0x000000ff) >> 0) + 1;
		break;
	case 0x84:
	case 0x86:
	case 0x92:
		coef = nv_rd32(device, 0x00e81c);
		P    = (coef & 0x00070000) >> 16;
		N    = (coef & 0x0000ff00) >> 8;
		M    = (coef & 0x000000ff) >> 0;
		break;
	case 0x94:
	case 0x96:
	case 0x98:
		rsel = nv_rd32(device, 0x00c050);
		switch (base) {
		case 0x4020: rsel = (rsel & 0x00000003) >> 0; break;
		case 0x4008: rsel = (rsel & 0x0000000c) >> 2; break;
		case 0x4028: rsel = (rsel & 0x00001800) >> 11; break;
		case 0x4030: rsel = 3; break;
		default:
			NV_ERROR(drm, "ref: bad pll 0x%06x\n", base);
			return 0;
		}

		switch (rsel) {
		case 0: id = 1; break;
		case 1: return read_clk(dev, clk_src_crystal);
		case 2: return read_clk(dev, clk_src_href);
		case 3: id = 0; break;
		}

		coef =  nv_rd32(device, 0x00e81c + (id * 0x28));
		P    = (nv_rd32(device, 0x00e824 + (id * 0x28)) >> 16) & 7;
		P   += (coef & 0x00070000) >> 16;
		N    = (coef & 0x0000ff00) >> 8;
		M    = (coef & 0x000000ff) >> 0;
		break;
	default:
		BUG_ON(1);
	}

	if (M)
		return (ref * N / M) >> P;
	return 0;
}