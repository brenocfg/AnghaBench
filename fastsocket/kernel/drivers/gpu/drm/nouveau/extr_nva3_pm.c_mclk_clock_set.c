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
struct TYPE_2__ {int pll; int clk; } ;
struct nva3_pm_state {int r004018; int* rammap; int* ramcfg; int r100760; TYPE_1__ mclk; } ;
struct nouveau_mem_exec_func {struct nva3_pm_state* priv; int /*<<< orphan*/  dev; } ;
struct nouveau_device {int dummy; } ;

/* Variables and functions */
 int ROM16 (int) ; 
 struct nouveau_device* nouveau_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_device*,int,int,int) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
mclk_clock_set(struct nouveau_mem_exec_func *exec)
{
	struct nouveau_device *device = nouveau_dev(exec->dev);
	struct nva3_pm_state *info = exec->priv;
	u32 ctrl;

	ctrl = nv_rd32(device, 0x004000);
	if (!(ctrl & 0x00000008) && info->mclk.pll) {
		nv_wr32(device, 0x004000, (ctrl |=  0x00000008));
		nv_mask(device, 0x1110e0, 0x00088000, 0x00088000);
		nv_wr32(device, 0x004018, 0x00001000);
		nv_wr32(device, 0x004000, (ctrl &= ~0x00000001));
		nv_wr32(device, 0x004004, info->mclk.pll);
		nv_wr32(device, 0x004000, (ctrl |=  0x00000001));
		udelay(64);
		nv_wr32(device, 0x004018, 0x00005000 | info->r004018);
		udelay(20);
	} else
	if (!info->mclk.pll) {
		nv_mask(device, 0x004168, 0x003f3040, info->mclk.clk);
		nv_wr32(device, 0x004000, (ctrl |= 0x00000008));
		nv_mask(device, 0x1110e0, 0x00088000, 0x00088000);
		nv_wr32(device, 0x004018, 0x0000d000 | info->r004018);
	}

	if (info->rammap) {
		if (info->ramcfg && (info->rammap[4] & 0x08)) {
			u32 unk5a0 = (ROM16(info->ramcfg[5]) << 8) |
				      info->ramcfg[5];
			u32 unk5a4 = ROM16(info->ramcfg[7]);
			u32 unk804 = (info->ramcfg[9] & 0xf0) << 16 |
				     (info->ramcfg[3] & 0x0f) << 16 |
				     (info->ramcfg[9] & 0x0f) |
				     0x80000000;
			nv_wr32(device, 0x1005a0, unk5a0);
			nv_wr32(device, 0x1005a4, unk5a4);
			nv_wr32(device, 0x10f804, unk804);
			nv_mask(device, 0x10053c, 0x00001000, 0x00000000);
		} else {
			nv_mask(device, 0x10053c, 0x00001000, 0x00001000);
			nv_mask(device, 0x10f804, 0x80000000, 0x00000000);
			nv_mask(device, 0x100760, 0x22222222, info->r100760);
			nv_mask(device, 0x1007a0, 0x22222222, info->r100760);
			nv_mask(device, 0x1007e0, 0x22222222, info->r100760);
		}
	}

	if (info->mclk.pll) {
		nv_mask(device, 0x1110e0, 0x00088000, 0x00011000);
		nv_wr32(device, 0x004000, (ctrl &= ~0x00000008));
	}
}