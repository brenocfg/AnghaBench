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
typedef  unsigned long u_int ;
struct TYPE_6__ {int bits_per_pixel; int xres; } ;
struct TYPE_4__ {int line_length; unsigned long smem_len; unsigned long smem_start; void* visual; } ;
struct fb_info {TYPE_3__ var; TYPE_1__ fix; } ;
struct TYPE_5__ {int palette_size; unsigned long screen_end; unsigned long vram_half_sam; scalar_t__ using_vram; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DMA_CR_D ; 
 int DMA_CR_E ; 
 void* FB_VISUAL_DIRECTCOLOR ; 
 void* FB_VISUAL_MONO10 ; 
 void* FB_VISUAL_PSEUDOCOLOR ; 
 void* FB_VISUAL_STATIC_PSEUDOCOLOR ; 
 int /*<<< orphan*/  IOMD_VIDCR ; 
 int /*<<< orphan*/  IOMD_VIDEND ; 
 int /*<<< orphan*/  IOMD_VIDSTART ; 
 int /*<<< orphan*/  VDMA_END ; 
 int /*<<< orphan*/  VDMA_START ; 
 unsigned long VDMA_XFERSIZE ; 
 void* VIDC_PALETTE_SIZE ; 
 int /*<<< orphan*/  acornfb_set_timing (struct fb_info*) ; 
 int /*<<< orphan*/  acornfb_update_dma (struct fb_info*,TYPE_3__*) ; 
 TYPE_2__ current_par ; 
 int /*<<< orphan*/  iomd_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memc_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int acornfb_set_par(struct fb_info *info)
{
	switch (info->var.bits_per_pixel) {
	case 1:
		current_par.palette_size = 2;
		info->fix.visual = FB_VISUAL_MONO10;
		break;
	case 2:
		current_par.palette_size = 4;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		break;
	case 4:
		current_par.palette_size = 16;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		break;
	case 8:
		current_par.palette_size = VIDC_PALETTE_SIZE;
#ifdef HAS_VIDC
		info->fix.visual = FB_VISUAL_STATIC_PSEUDOCOLOR;
#else
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
#endif
		break;
#ifdef HAS_VIDC20
	case 16:
		current_par.palette_size = 32;
		info->fix.visual = FB_VISUAL_DIRECTCOLOR;
		break;
	case 32:
		current_par.palette_size = VIDC_PALETTE_SIZE;
		info->fix.visual = FB_VISUAL_DIRECTCOLOR;
		break;
#endif
	default:
		BUG();
	}

	info->fix.line_length	= (info->var.xres * info->var.bits_per_pixel) / 8;

#if defined(HAS_MEMC)
	{
		unsigned long size = info->fix.smem_len - VDMA_XFERSIZE;

		memc_write(VDMA_START, 0);
		memc_write(VDMA_END, size >> 2);
	}
#elif defined(HAS_IOMD)
	{
		unsigned long start, size;
		u_int control;

		start = info->fix.smem_start;
		size  = current_par.screen_end;

		if (current_par.using_vram) {
			size -= current_par.vram_half_sam;
			control = DMA_CR_E | (current_par.vram_half_sam / 256);
		} else {
			size -= 16;
			control = DMA_CR_E | DMA_CR_D | 16;
		}

		iomd_writel(start,   IOMD_VIDSTART);
		iomd_writel(size,    IOMD_VIDEND);
		iomd_writel(control, IOMD_VIDCR);
	}
#endif

	acornfb_update_dma(info, &info->var);
	acornfb_set_timing(info);

	return 0;
}