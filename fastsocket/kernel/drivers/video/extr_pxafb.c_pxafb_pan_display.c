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
struct pxafb_info {scalar_t__ state; int lccr0; int* fdadr; } ;
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ C_ENABLE ; 
 int DMA_BASE ; 
 int DMA_MAX ; 
 int /*<<< orphan*/  FBR0 ; 
 int /*<<< orphan*/  FBR1 ; 
 int LCCR0_SDS ; 
 int /*<<< orphan*/  lcd_writel (struct pxafb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_base_frame (struct pxafb_info*,int) ; 

__attribute__((used)) static int pxafb_pan_display(struct fb_var_screeninfo *var,
			     struct fb_info *info)
{
	struct pxafb_info *fbi = (struct pxafb_info *)info;
	int dma = DMA_MAX + DMA_BASE;

	if (fbi->state != C_ENABLE)
		return 0;

	setup_base_frame(fbi, 1);

	if (fbi->lccr0 & LCCR0_SDS)
		lcd_writel(fbi, FBR1, fbi->fdadr[dma + 1] | 0x1);

	lcd_writel(fbi, FBR0, fbi->fdadr[dma] | 0x1);
	return 0;
}