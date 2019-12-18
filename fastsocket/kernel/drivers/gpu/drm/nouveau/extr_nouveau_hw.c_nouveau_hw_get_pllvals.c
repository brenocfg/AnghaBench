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
typedef  int uint32_t ;
struct nvbios_pll {int reg; int /*<<< orphan*/  refclk; } ;
struct nouveau_pll_vals {int /*<<< orphan*/  refclk; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_device {int card_type; } ;
struct nouveau_bios {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum nvbios_pll_type { ____Placeholder_nvbios_pll_type } nvbios_pll_type ;

/* Variables and functions */
 int ENOENT ; 
 int NVReadRAMDAC (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_PRAMDAC_580 ; 
 int NV_PRAMDAC_VPLL_COEFF ; 
 int NV_RAMDAC_580_VPLL1_ACTIVE ; 
 int NV_RAMDAC_580_VPLL2_ACTIVE ; 
 int NV_RAMDAC_VPLL2 ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_hw_decode_pll (struct drm_device*,int,int,int,struct nouveau_pll_vals*) ; 
 struct nouveau_device* nv_device (int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 scalar_t__ nv_two_reg_pll (struct drm_device*) ; 
 int nvbios_pll_parse (struct nouveau_bios*,int,struct nvbios_pll*) ; 

int
nouveau_hw_get_pllvals(struct drm_device *dev, enum nvbios_pll_type plltype,
		       struct nouveau_pll_vals *pllvals)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_device *device = nv_device(drm->device);
	struct nouveau_bios *bios = nouveau_bios(device);
	uint32_t reg1, pll1, pll2 = 0;
	struct nvbios_pll pll_lim;
	int ret;

	ret = nvbios_pll_parse(bios, plltype, &pll_lim);
	if (ret || !(reg1 = pll_lim.reg))
		return -ENOENT;

	pll1 = nv_rd32(device, reg1);
	if (reg1 <= 0x405c)
		pll2 = nv_rd32(device, reg1 + 4);
	else if (nv_two_reg_pll(dev)) {
		uint32_t reg2 = reg1 + (reg1 == NV_RAMDAC_VPLL2 ? 0x5c : 0x70);

		pll2 = nv_rd32(device, reg2);
	}

	if (nv_device(drm->device)->card_type == 0x40 && reg1 >= NV_PRAMDAC_VPLL_COEFF) {
		uint32_t ramdac580 = NVReadRAMDAC(dev, 0, NV_PRAMDAC_580);

		/* check whether vpll has been forced into single stage mode */
		if (reg1 == NV_PRAMDAC_VPLL_COEFF) {
			if (ramdac580 & NV_RAMDAC_580_VPLL1_ACTIVE)
				pll2 = 0;
		} else
			if (ramdac580 & NV_RAMDAC_580_VPLL2_ACTIVE)
				pll2 = 0;
	}

	nouveau_hw_decode_pll(dev, reg1, pll1, pll2, pllvals);
	pllvals->refclk = pll_lim.refclk;
	return 0;
}