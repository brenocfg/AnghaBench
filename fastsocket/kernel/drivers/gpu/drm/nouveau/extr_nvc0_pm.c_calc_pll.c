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
struct nouveau_device {int dummy; } ;
struct nouveau_bios {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_bios* nouveau_bios (struct nouveau_device*) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 int nva3_calc_pll (struct drm_device*,struct nvbios_pll*,int,int*,int /*<<< orphan*/ *,int*,int*) ; 
 int nvbios_pll_parse (struct nouveau_bios*,int,struct nvbios_pll*) ; 
 int /*<<< orphan*/  read_div (struct drm_device*,int,int,int) ; 

__attribute__((used)) static u32
calc_pll(struct drm_device *dev, int clk, u32 freq, u32 *coef)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_bios *bios = nouveau_bios(device);
	struct nvbios_pll limits;
	int N, M, P, ret;

	ret = nvbios_pll_parse(bios, 0x137000 + (clk * 0x20), &limits);
	if (ret)
		return 0;

	limits.refclk = read_div(dev, clk, 0x137120, 0x137140);
	if (!limits.refclk)
		return 0;

	ret = nva3_calc_pll(dev, &limits, freq, &N, NULL, &M, &P);
	if (ret <= 0)
		return 0;

	*coef = (P << 16) | (N << 8) | M;
	return ret;
}