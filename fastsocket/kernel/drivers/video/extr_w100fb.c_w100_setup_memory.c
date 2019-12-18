#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mc_fb_start; int mc_fb_top; } ;
union mc_fb_location_u {scalar_t__ val; TYPE_1__ f; } ;
struct TYPE_5__ {int mc_ext_mem_start; int mc_ext_mem_top; } ;
union mc_ext_mem_location_u {scalar_t__ val; TYPE_2__ f; } ;
typedef  int u32 ;
struct w100fb_par {TYPE_3__* mach; int /*<<< orphan*/  extmem_active; } ;
struct w100_mem_info {int size; int ext_cntl; int sdram_mode_reg; int ext_timing_cntl; int io_cntl; } ;
struct w100_bm_mem_info {int ext_mem_bw; int offset; int ext_timing_ctl; int ext_cntl; int mode_reg; int io_cntl; int config; } ;
struct TYPE_6__ {struct w100_mem_info* mem; struct w100_bm_mem_info* bm_mem; } ;

/* Variables and functions */
 int MEM_EXT_BASE_VALUE ; 
 int MEM_INT_BASE_VALUE ; 
 int MEM_INT_SIZE ; 
 int W100_FB_BASE ; 
 int /*<<< orphan*/  W100_SUSPEND_EXTMEM ; 
 scalar_t__ mmBM_CONFIG ; 
 scalar_t__ mmBM_EXT_MEM_BANDWIDTH ; 
 scalar_t__ mmBM_MEM_EXT_CNTL ; 
 scalar_t__ mmBM_MEM_EXT_TIMING_CNTL ; 
 scalar_t__ mmBM_MEM_IO_CNTL ; 
 scalar_t__ mmBM_MEM_MODE_REG ; 
 scalar_t__ mmBM_OFFSET ; 
 scalar_t__ mmMC_BIST_CTRL ; 
 scalar_t__ mmMC_EXT_MEM_LOCATION ; 
 scalar_t__ mmMC_FB_LOCATION ; 
 scalar_t__ mmMEM_EXT_CNTL ; 
 scalar_t__ mmMEM_EXT_TIMING_CNTL ; 
 scalar_t__ mmMEM_IO_CNTL ; 
 scalar_t__ mmMEM_SDRAM_MODE_REG ; 
 scalar_t__ remapped_regs ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w100_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void w100_setup_memory(struct w100fb_par *par)
{
	union mc_ext_mem_location_u extmem_location;
	union mc_fb_location_u intmem_location;
	struct w100_mem_info *mem = par->mach->mem;
	struct w100_bm_mem_info *bm_mem = par->mach->bm_mem;

	if (!par->extmem_active) {
		w100_suspend(W100_SUSPEND_EXTMEM);

		/* Map Internal Memory at FB Base */
		intmem_location.f.mc_fb_start = W100_FB_BASE >> 8;
		intmem_location.f.mc_fb_top = (W100_FB_BASE+MEM_INT_SIZE) >> 8;
		writel((u32) (intmem_location.val), remapped_regs + mmMC_FB_LOCATION);

		/* Unmap External Memory - value is *probably* irrelevant but may have meaning
		   to acceleration libraries */
		extmem_location.f.mc_ext_mem_start = MEM_EXT_BASE_VALUE >> 8;
		extmem_location.f.mc_ext_mem_top = (MEM_EXT_BASE_VALUE-1) >> 8;
		writel((u32) (extmem_location.val), remapped_regs + mmMC_EXT_MEM_LOCATION);
	} else {
		/* Map Internal Memory to its default location */
		intmem_location.f.mc_fb_start = MEM_INT_BASE_VALUE >> 8;
		intmem_location.f.mc_fb_top = (MEM_INT_BASE_VALUE+MEM_INT_SIZE) >> 8;
		writel((u32) (intmem_location.val), remapped_regs + mmMC_FB_LOCATION);

		/* Map External Memory at FB Base */
		extmem_location.f.mc_ext_mem_start = W100_FB_BASE >> 8;
		extmem_location.f.mc_ext_mem_top = (W100_FB_BASE+par->mach->mem->size) >> 8;
		writel((u32) (extmem_location.val), remapped_regs + mmMC_EXT_MEM_LOCATION);

		writel(0x00007800, remapped_regs + mmMC_BIST_CTRL);
		writel(mem->ext_cntl, remapped_regs + mmMEM_EXT_CNTL);
		writel(0x00200021, remapped_regs + mmMEM_SDRAM_MODE_REG);
		udelay(100);
		writel(0x80200021, remapped_regs + mmMEM_SDRAM_MODE_REG);
		udelay(100);
		writel(mem->sdram_mode_reg, remapped_regs + mmMEM_SDRAM_MODE_REG);
		udelay(100);
		writel(mem->ext_timing_cntl, remapped_regs + mmMEM_EXT_TIMING_CNTL);
		writel(mem->io_cntl, remapped_regs + mmMEM_IO_CNTL);
		if (bm_mem) {
			writel(bm_mem->ext_mem_bw, remapped_regs + mmBM_EXT_MEM_BANDWIDTH);
			writel(bm_mem->offset, remapped_regs + mmBM_OFFSET);
			writel(bm_mem->ext_timing_ctl, remapped_regs + mmBM_MEM_EXT_TIMING_CNTL);
			writel(bm_mem->ext_cntl, remapped_regs + mmBM_MEM_EXT_CNTL);
			writel(bm_mem->mode_reg, remapped_regs + mmBM_MEM_MODE_REG);
			writel(bm_mem->io_cntl, remapped_regs + mmBM_MEM_IO_CNTL);
			writel(bm_mem->config, remapped_regs + mmBM_CONFIG);
		}
	}
}