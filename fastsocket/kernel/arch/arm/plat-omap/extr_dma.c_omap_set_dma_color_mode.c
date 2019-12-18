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
typedef  int u16 ;
typedef  enum omap_dma_color_mode { ____Placeholder_omap_dma_color_mode } omap_dma_color_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCR (int) ; 
 int /*<<< orphan*/  CCR2 (int) ; 
 int /*<<< orphan*/  COLOR (int) ; 
 int /*<<< orphan*/  COLOR_L (int) ; 
 int /*<<< orphan*/  COLOR_U (int) ; 
 int /*<<< orphan*/  LCH_CTRL (int) ; 
#define  OMAP_DMA_COLOR_DIS 130 
#define  OMAP_DMA_CONSTANT_FILL 129 
#define  OMAP_DMA_TRANSPARENT_COPY 128 
 scalar_t__ cpu_class_is_omap1 () ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 int dma_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dma_in_1510_mode () ; 

void omap_set_dma_color_mode(int lch, enum omap_dma_color_mode mode, u32 color)
{
	BUG_ON(omap_dma_in_1510_mode());

	if (cpu_class_is_omap1()) {
		u16 w;

		w = dma_read(CCR2(lch));
		w &= ~0x03;

		switch (mode) {
		case OMAP_DMA_CONSTANT_FILL:
			w |= 0x01;
			break;
		case OMAP_DMA_TRANSPARENT_COPY:
			w |= 0x02;
			break;
		case OMAP_DMA_COLOR_DIS:
			break;
		default:
			BUG();
		}
		dma_write(w, CCR2(lch));

		w = dma_read(LCH_CTRL(lch));
		w &= ~0x0f;
		/* Default is channel type 2D */
		if (mode) {
			dma_write((u16)color, COLOR_L(lch));
			dma_write((u16)(color >> 16), COLOR_U(lch));
			w |= 1;		/* Channel type G */
		}
		dma_write(w, LCH_CTRL(lch));
	}

	if (cpu_class_is_omap2()) {
		u32 val;

		val = dma_read(CCR(lch));
		val &= ~((1 << 17) | (1 << 16));

		switch (mode) {
		case OMAP_DMA_CONSTANT_FILL:
			val |= 1 << 16;
			break;
		case OMAP_DMA_TRANSPARENT_COPY:
			val |= 1 << 17;
			break;
		case OMAP_DMA_COLOR_DIS:
			break;
		default:
			BUG();
		}
		dma_write(val, CCR(lch));

		color &= 0xffffff;
		dma_write(color, COLOR(lch));
	}
}