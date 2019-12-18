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
struct vga16fb_par {int vesa_blanked; int palette_blanked; } ;
struct fb_info {struct vga16fb_par* par; } ;

/* Variables and functions */
#define  FB_BLANK_NORMAL 129 
#define  FB_BLANK_UNBLANK 128 
 int /*<<< orphan*/  vga_pal_blank () ; 
 int /*<<< orphan*/  vga_vesa_blank (struct vga16fb_par*,int) ; 
 int /*<<< orphan*/  vga_vesa_unblank (struct vga16fb_par*) ; 

__attribute__((used)) static int vga16fb_blank(int blank, struct fb_info *info)
{
	struct vga16fb_par *par = info->par;

	switch (blank) {
	case FB_BLANK_UNBLANK:				/* Unblank */
		if (par->vesa_blanked) {
			vga_vesa_unblank(par);
			par->vesa_blanked = 0;
		}
		if (par->palette_blanked) {
			par->palette_blanked = 0;
		}
		break;
	case FB_BLANK_NORMAL:				/* blank */
		vga_pal_blank();
		par->palette_blanked = 1;
		break;
	default:			/* VESA blanking */
		vga_vesa_blank(par, blank);
		par->vesa_blanked = 1;
		break;
	}
	return 0;
}