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
struct nvc0_pm_clock {int coef; } ;
struct nvbios_pll {scalar_t__ refclk; } ;
struct nouveau_device {int dummy; } ;
struct nouveau_bios {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_device*) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_device*,int,int,int) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int /*<<< orphan*/  nv_wait (struct nouveau_device*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int,int) ; 
 int nva3_calc_pll (struct drm_device*,struct nvbios_pll*,int,int*,int /*<<< orphan*/ *,int*,int*) ; 
 int nvbios_pll_parse (struct nouveau_bios*,int,struct nvbios_pll*) ; 
 scalar_t__ read_pll (struct drm_device*,int) ; 

__attribute__((used)) static int
calc_mem(struct drm_device *dev, struct nvc0_pm_clock *info, u32 freq)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_bios *bios = nouveau_bios(device);
	struct nvbios_pll pll;
	int N, M, P, ret;
	u32 ctrl;

	/* mclk pll input freq comes from another pll, make sure it's on */
	ctrl = nv_rd32(device, 0x132020);
	if (!(ctrl & 0x00000001)) {
		/* if not, program it to 567MHz.  nfi where this value comes
		 * from - it looks like it's in the pll limits table for
		 * 132000 but the binary driver ignores all my attempts to
		 * change this value.
		 */
		nv_wr32(device, 0x137320, 0x00000103);
		nv_wr32(device, 0x137330, 0x81200606);
		nv_wait(device, 0x132020, 0x00010000, 0x00010000);
		nv_wr32(device, 0x132024, 0x0001150f);
		nv_mask(device, 0x132020, 0x00000001, 0x00000001);
		nv_wait(device, 0x137390, 0x00020000, 0x00020000);
		nv_mask(device, 0x132020, 0x00000004, 0x00000004);
	}

	/* for the moment, until the clock tree is better understood, use
	 * pll mode for all clock frequencies
	 */
	ret = nvbios_pll_parse(bios, 0x132000, &pll);
	if (ret == 0) {
		pll.refclk = read_pll(dev, 0x132020);
		if (pll.refclk) {
			ret = nva3_calc_pll(dev, &pll, freq, &N, NULL, &M, &P);
			if (ret > 0) {
				info->coef = (P << 16) | (N << 8) | M;
				return 0;
			}
		}
	}

	return -EINVAL;
}