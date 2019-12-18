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
typedef  int u8 ;
struct savagefb_par {scalar_t__ display_type; } ;
struct fb_info {struct savagefb_par* par; } ;

/* Variables and functions */
 scalar_t__ DISP_CRT ; 
 scalar_t__ DISP_DFP ; 
 scalar_t__ DISP_LCD ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int vga_in8 (int,struct savagefb_par*) ; 
 int /*<<< orphan*/  vga_out8 (int,int,struct savagefb_par*) ; 

__attribute__((used)) static int savagefb_blank(int blank, struct fb_info *info)
{
	struct savagefb_par *par = info->par;
	u8 sr8 = 0, srd = 0;

	if (par->display_type == DISP_CRT) {
		vga_out8(0x3c4, 0x08, par);
		sr8 = vga_in8(0x3c5, par);
		sr8 |= 0x06;
		vga_out8(0x3c5, sr8, par);
		vga_out8(0x3c4, 0x0d, par);
		srd = vga_in8(0x3c5, par);
		srd &= 0x50;

		switch (blank) {
		case FB_BLANK_UNBLANK:
		case FB_BLANK_NORMAL:
			break;
		case FB_BLANK_VSYNC_SUSPEND:
			srd |= 0x10;
			break;
		case FB_BLANK_HSYNC_SUSPEND:
			srd |= 0x40;
			break;
		case FB_BLANK_POWERDOWN:
			srd |= 0x50;
			break;
		}

		vga_out8(0x3c4, 0x0d, par);
		vga_out8(0x3c5, srd, par);
	}

	if (par->display_type == DISP_LCD ||
	    par->display_type == DISP_DFP) {
		switch(blank) {
		case FB_BLANK_UNBLANK:
		case FB_BLANK_NORMAL:
			vga_out8(0x3c4, 0x31, par); /* SR31 bit 4 - FP enable */
			vga_out8(0x3c5, vga_in8(0x3c5, par) | 0x10, par);
			break;
		case FB_BLANK_VSYNC_SUSPEND:
		case FB_BLANK_HSYNC_SUSPEND:
		case FB_BLANK_POWERDOWN:
			vga_out8(0x3c4, 0x31, par); /* SR31 bit 4 - FP enable */
			vga_out8(0x3c5, vga_in8(0x3c5, par) & ~0x10, par);
			break;
		}
	}

	return (blank == FB_BLANK_NORMAL) ? 1 : 0;
}