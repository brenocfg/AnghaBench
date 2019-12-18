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
struct pxa168fb_info {scalar_t__ reg_base; } ;

/* Variables and functions */
 int FB_SYNC_VERT_HIGH_ACT ; 
 scalar_t__ LCD_SPU_DMA_CTRL1 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void set_dma_control1(struct pxa168fb_info *fbi, int sync)
{
	u32 x;

	/*
	 * Configure default bits: vsync triggers DMA, gated clock
	 * enable, power save enable, configure alpha registers to
	 * display 100% graphics, and set pixel command.
	 */
	x = readl(fbi->reg_base + LCD_SPU_DMA_CTRL1);
	x |= 0x2032ff81;

	/*
	 * We trigger DMA on the falling edge of vsync if vsync is
	 * active low, or on the rising edge if vsync is active high.
	 */
	if (!(sync & FB_SYNC_VERT_HIGH_ACT))
		x |= 0x08000000;

	writel(x, fbi->reg_base + LCD_SPU_DMA_CTRL1);
}