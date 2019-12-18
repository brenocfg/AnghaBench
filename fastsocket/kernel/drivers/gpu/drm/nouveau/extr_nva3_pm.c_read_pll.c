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
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int read_clk (struct drm_device*,int,int) ; 

__attribute__((used)) static u32
read_pll(struct drm_device *dev, int clk, u32 pll)
{
	struct nouveau_device *device = nouveau_dev(dev);
	u32 ctrl = nv_rd32(device, pll + 0);
	u32 sclk = 0, P = 1, N = 1, M = 1;

	if (!(ctrl & 0x00000008)) {
		if (ctrl & 0x00000001) {
			u32 coef = nv_rd32(device, pll + 4);
			M = (coef & 0x000000ff) >> 0;
			N = (coef & 0x0000ff00) >> 8;
			P = (coef & 0x003f0000) >> 16;

			/* no post-divider on these.. */
			if ((pll & 0x00ff00) == 0x00e800)
				P = 1;

			sclk = read_clk(dev, 0x00 + clk, false);
		}
	} else {
		sclk = read_clk(dev, 0x10 + clk, false);
	}

	if (M * P)
		return sclk * N / (M * P);
	return 0;
}