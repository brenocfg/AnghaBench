#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ max_freq; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_freq; } ;
struct nvbios_pll {TYPE_2__ vco2; TYPE_1__ vco1; } ;
struct nouveau_pll_vals {int N1; int M1; int N2; int M2; int log2P; } ;
struct nouveau_device {int dummy; } ;
struct nouveau_clock {int /*<<< orphan*/  (* pll_calc ) (struct nouveau_clock*,struct nvbios_pll*,int /*<<< orphan*/ ,struct nouveau_pll_vals*) ;} ;
struct nouveau_bios {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_device*) ; 
 struct nouveau_clock* nouveau_clock (struct nouveau_device*) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 int nvbios_pll_parse (struct nouveau_bios*,int /*<<< orphan*/ ,struct nvbios_pll*) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_clock*,struct nvbios_pll*,int /*<<< orphan*/ ,struct nouveau_pll_vals*) ; 

__attribute__((used)) static int
nv40_calc_pll(struct drm_device *dev, u32 reg, struct nvbios_pll *pll,
	      u32 clk, int *N1, int *M1, int *N2, int *M2, int *log2P)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_bios *bios = nouveau_bios(device);
	struct nouveau_clock *pclk = nouveau_clock(device);
	struct nouveau_pll_vals coef;
	int ret;

	ret = nvbios_pll_parse(bios, reg, pll);
	if (ret)
		return ret;

	if (clk < pll->vco1.max_freq)
		pll->vco2.max_freq = 0;

	pclk->pll_calc(pclk, pll, clk, &coef);
	if (ret == 0)
		return -ERANGE;

	*N1 = coef.N1;
	*M1 = coef.M1;
	if (N2 && M2) {
		if (pll->vco2.max_freq) {
			*N2 = coef.N2;
			*M2 = coef.M2;
		} else {
			*N2 = 1;
			*M2 = 1;
		}
	}
	*log2P = coef.log2P;
	return 0;
}