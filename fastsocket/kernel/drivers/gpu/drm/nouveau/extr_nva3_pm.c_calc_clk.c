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
struct nvbios_pll {int /*<<< orphan*/  refclk; } ;
struct nouveau_drm {int dummy; } ;
struct nouveau_device {int dummy; } ;
struct nouveau_bios {int dummy; } ;
struct drm_device {int dummy; } ;
struct creg {int pll; int clk; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int,int) ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int,int,int) ; 
 int min (int,int) ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_device*) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int nva3_calc_pll (struct drm_device*,struct nvbios_pll*,int,int*,int /*<<< orphan*/ *,int*,int*) ; 
 int nvbios_pll_parse (struct nouveau_bios*,int,struct nvbios_pll*) ; 
 int /*<<< orphan*/  read_clk (struct drm_device*,int,int) ; 
 int read_vco (struct drm_device*,int) ; 

__attribute__((used)) static int
calc_clk(struct drm_device *dev, int clk, u32 pll, u32 khz, struct creg *reg)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_bios *bios = nouveau_bios(device);
	struct nvbios_pll limits;
	u32 oclk, sclk, sdiv;
	int P, N, M, diff;
	int ret;

	reg->pll = 0;
	reg->clk = 0;
	if (!khz) {
		NV_DEBUG(drm, "no clock for 0x%04x/0x%02x\n", pll, clk);
		return 0;
	}

	switch (khz) {
	case 27000:
		reg->clk = 0x00000100;
		return khz;
	case 100000:
		reg->clk = 0x00002100;
		return khz;
	case 108000:
		reg->clk = 0x00002140;
		return khz;
	default:
		sclk = read_vco(dev, clk);
		sdiv = min((sclk * 2) / (khz - 2999), (u32)65);
		/* if the clock has a PLL attached, and we can get a within
		 * [-2, 3) MHz of a divider, we'll disable the PLL and use
		 * the divider instead.
		 *
		 * divider can go as low as 2, limited here because NVIDIA
		 * and the VBIOS on my NVA8 seem to prefer using the PLL
		 * for 810MHz - is there a good reason?
		 */
		if (sdiv > 4) {
			oclk = (sclk * 2) / sdiv;
			diff = khz - oclk;
			if (!pll || (diff >= -2000 && diff < 3000)) {
				reg->clk = (((sdiv - 2) << 16) | 0x00003100);
				return oclk;
			}
		}

		if (!pll) {
			NV_ERROR(drm, "bad freq %02x: %d %d\n", clk, khz, sclk);
			return -ERANGE;
		}

		break;
	}

	ret = nvbios_pll_parse(bios, pll, &limits);
	if (ret)
		return ret;

	limits.refclk = read_clk(dev, clk - 0x10, true);
	if (!limits.refclk)
		return -EINVAL;

	ret = nva3_calc_pll(dev, &limits, khz, &N, NULL, &M, &P);
	if (ret >= 0) {
		reg->clk = nv_rd32(device, 0x4120 + (clk * 4));
		reg->pll = (P << 16) | (N << 8) | M;
	}

	return ret;
}