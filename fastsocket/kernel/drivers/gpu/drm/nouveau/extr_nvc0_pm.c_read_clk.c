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
 int read_pll (struct drm_device*,int) ; 

__attribute__((used)) static u32
read_clk(struct drm_device *dev, int clk)
{
	struct nouveau_device *device = nouveau_dev(dev);
	u32 sctl = nv_rd32(device, 0x137250 + (clk * 4));
	u32 ssel = nv_rd32(device, 0x137100);
	u32 sclk, sdiv;

	if (ssel & (1 << clk)) {
		if (clk < 7)
			sclk = read_pll(dev, 0x137000 + (clk * 0x20));
		else
			sclk = read_pll(dev, 0x1370e0);
		sdiv = ((sctl & 0x00003f00) >> 8) + 2;
	} else {
		sclk = read_div(dev, clk, 0x137160, 0x1371d0);
		sdiv = ((sctl & 0x0000003f) >> 0) + 2;
	}

	if (sctl & 0x80000000)
		return (sclk * 2) / sdiv;
	return sclk;
}