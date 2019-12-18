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
struct nouveau_device {int crystal; } ;
struct drm_device {int dummy; } ;
typedef  enum clk_src { ____Placeholder_clk_src } clk_src ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int,int) ; 
#define  clk_src_crystal 138 
#define  clk_src_dom6 137 
#define  clk_src_hclk 136 
#define  clk_src_hclkm3 135 
#define  clk_src_hclkm3d2 134 
#define  clk_src_host 133 
#define  clk_src_href 132 
#define  clk_src_mclk 131 
#define  clk_src_nvclk 130 
#define  clk_src_sclk 129 
#define  clk_src_vdec 128 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int read_div (struct drm_device*) ; 
 int read_pll (struct drm_device*,int) ; 

__attribute__((used)) static u32
read_clk(struct drm_device *dev, enum clk_src src)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_drm *drm = nouveau_drm(dev);
	u32 mast = nv_rd32(device, 0x00c040);
	u32 P = 0;

	switch (src) {
	case clk_src_crystal:
		return device->crystal;
	case clk_src_href:
		return 100000; /* PCIE reference clock */
	case clk_src_hclk:
		return read_clk(dev, clk_src_href) * 27778 / 10000;
	case clk_src_hclkm3:
		return read_clk(dev, clk_src_hclk) * 3;
	case clk_src_hclkm3d2:
		return read_clk(dev, clk_src_hclk) * 3 / 2;
	case clk_src_host:
		switch (mast & 0x30000000) {
		case 0x00000000: return read_clk(dev, clk_src_href);
		case 0x10000000: break;
		case 0x20000000: /* !0x50 */
		case 0x30000000: return read_clk(dev, clk_src_hclk);
		}
		break;
	case clk_src_nvclk:
		if (!(mast & 0x00100000))
			P = (nv_rd32(device, 0x004028) & 0x00070000) >> 16;
		switch (mast & 0x00000003) {
		case 0x00000000: return read_clk(dev, clk_src_crystal) >> P;
		case 0x00000001: return read_clk(dev, clk_src_dom6);
		case 0x00000002: return read_pll(dev, 0x004020) >> P;
		case 0x00000003: return read_pll(dev, 0x004028) >> P;
		}
		break;
	case clk_src_sclk:
		P = (nv_rd32(device, 0x004020) & 0x00070000) >> 16;
		switch (mast & 0x00000030) {
		case 0x00000000:
			if (mast & 0x00000080)
				return read_clk(dev, clk_src_host) >> P;
			return read_clk(dev, clk_src_crystal) >> P;
		case 0x00000010: break;
		case 0x00000020: return read_pll(dev, 0x004028) >> P;
		case 0x00000030: return read_pll(dev, 0x004020) >> P;
		}
		break;
	case clk_src_mclk:
		P = (nv_rd32(device, 0x004008) & 0x00070000) >> 16;
		if (nv_rd32(device, 0x004008) & 0x00000200) {
			switch (mast & 0x0000c000) {
			case 0x00000000:
				return read_clk(dev, clk_src_crystal) >> P;
			case 0x00008000:
			case 0x0000c000:
				return read_clk(dev, clk_src_href) >> P;
			}
		} else {
			return read_pll(dev, 0x004008) >> P;
		}
		break;
	case clk_src_vdec:
		P = (read_div(dev) & 0x00000700) >> 8;
		switch (nv_device(drm->device)->chipset) {
		case 0x84:
		case 0x86:
		case 0x92:
		case 0x94:
		case 0x96:
		case 0xa0:
			switch (mast & 0x00000c00) {
			case 0x00000000:
				if (nv_device(drm->device)->chipset == 0xa0) /* wtf?? */
					return read_clk(dev, clk_src_nvclk) >> P;
				return read_clk(dev, clk_src_crystal) >> P;
			case 0x00000400:
				return 0;
			case 0x00000800:
				if (mast & 0x01000000)
					return read_pll(dev, 0x004028) >> P;
				return read_pll(dev, 0x004030) >> P;
			case 0x00000c00:
				return read_clk(dev, clk_src_nvclk) >> P;
			}
			break;
		case 0x98:
			switch (mast & 0x00000c00) {
			case 0x00000000:
				return read_clk(dev, clk_src_nvclk) >> P;
			case 0x00000400:
				return 0;
			case 0x00000800:
				return read_clk(dev, clk_src_hclkm3d2) >> P;
			case 0x00000c00:
				return read_clk(dev, clk_src_mclk) >> P;
			}
			break;
		}
		break;
	case clk_src_dom6:
		switch (nv_device(drm->device)->chipset) {
		case 0x50:
		case 0xa0:
			return read_pll(dev, 0x00e810) >> 2;
		case 0x84:
		case 0x86:
		case 0x92:
		case 0x94:
		case 0x96:
		case 0x98:
			P = (read_div(dev) & 0x00000007) >> 0;
			switch (mast & 0x0c000000) {
			case 0x00000000: return read_clk(dev, clk_src_href);
			case 0x04000000: break;
			case 0x08000000: return read_clk(dev, clk_src_hclk);
			case 0x0c000000:
				return read_clk(dev, clk_src_hclkm3) >> P;
			}
			break;
		default:
			break;
		}
	default:
		break;
	}

	NV_DEBUG(drm, "unknown clock source %d 0x%08x\n", src, mast);
	return 0;
}