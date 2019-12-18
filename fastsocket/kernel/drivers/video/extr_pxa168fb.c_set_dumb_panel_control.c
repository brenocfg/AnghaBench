#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pxa168fb_mach_info {int dumb_mode; int gpio_output_data; int gpio_output_mask; scalar_t__ invert_pixclock; scalar_t__ invert_pix_val_ena; scalar_t__ invert_composite_blank; scalar_t__ panel_rgb_reverse_lanes; } ;
struct pxa168fb_info {scalar_t__ reg_base; scalar_t__ is_blanked; TYPE_1__* dev; } ;
struct TYPE_4__ {int sync; } ;
struct fb_info {TYPE_2__ var; struct pxa168fb_info* par; } ;
struct TYPE_3__ {struct pxa168fb_mach_info* platform_data; } ;

/* Variables and functions */
 int FB_SYNC_COMP_HIGH_ACT ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 scalar_t__ LCD_SPU_DUMB_CTRL ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void set_dumb_panel_control(struct fb_info *info)
{
	struct pxa168fb_info *fbi = info->par;
	struct pxa168fb_mach_info *mi = fbi->dev->platform_data;
	u32 x;

	/*
	 * Preserve enable flag.
	 */
	x = readl(fbi->reg_base + LCD_SPU_DUMB_CTRL) & 0x00000001;

	x |= (fbi->is_blanked ? 0x7 : mi->dumb_mode) << 28;
	x |= mi->gpio_output_data << 20;
	x |= mi->gpio_output_mask << 12;
	x |= mi->panel_rgb_reverse_lanes ? 0x00000080 : 0;
	x |= mi->invert_composite_blank ? 0x00000040 : 0;
	x |= (info->var.sync & FB_SYNC_COMP_HIGH_ACT) ? 0x00000020 : 0;
	x |= mi->invert_pix_val_ena ? 0x00000010 : 0;
	x |= (info->var.sync & FB_SYNC_VERT_HIGH_ACT) ? 0 : 0x00000008;
	x |= (info->var.sync & FB_SYNC_HOR_HIGH_ACT) ? 0 : 0x00000004;
	x |= mi->invert_pixclock ? 0x00000002 : 0;

	writel(x, fbi->reg_base + LCD_SPU_DUMB_CTRL);
}