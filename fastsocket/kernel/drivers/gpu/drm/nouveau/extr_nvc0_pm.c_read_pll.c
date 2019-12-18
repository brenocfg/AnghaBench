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
 int read_div (struct drm_device*,int,int,int) ; 

__attribute__((used)) static u32
read_pll(struct drm_device *dev, u32 pll)
{
	struct nouveau_device *device = nouveau_dev(dev);
	u32 ctrl = nv_rd32(device, pll + 0);
	u32 coef = nv_rd32(device, pll + 4);
	u32 P = (coef & 0x003f0000) >> 16;
	u32 N = (coef & 0x0000ff00) >> 8;
	u32 M = (coef & 0x000000ff) >> 0;
	u32 sclk, doff;

	if (!(ctrl & 0x00000001))
		return 0;

	switch (pll & 0xfff000) {
	case 0x00e000:
		sclk = 27000;
		P = 1;
		break;
	case 0x137000:
		doff = (pll - 0x137000) / 0x20;
		sclk = read_div(dev, doff, 0x137120, 0x137140);
		break;
	case 0x132000:
		switch (pll) {
		case 0x132000:
			sclk = read_pll(dev, 0x132020);
			break;
		case 0x132020:
			sclk = read_div(dev, 0, 0x137320, 0x137330);
			break;
		default:
			return 0;
		}
		break;
	default:
		return 0;
	}

	return sclk * N / M / P;
}