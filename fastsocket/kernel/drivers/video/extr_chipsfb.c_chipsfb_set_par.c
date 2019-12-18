#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int offset; int length; } ;
struct TYPE_8__ {int offset; int length; } ;
struct TYPE_7__ {int offset; int length; } ;
struct TYPE_10__ {int bits_per_pixel; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct TYPE_6__ {int line_length; int /*<<< orphan*/  visual; } ;
struct fb_info {TYPE_5__ var; TYPE_1__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  write_cr (int,int) ; 
 int /*<<< orphan*/  write_xr (int,int) ; 

__attribute__((used)) static int chipsfb_set_par(struct fb_info *info)
{
	if (info->var.bits_per_pixel == 16) {
		write_cr(0x13, 200);		// Set line length (doublewords)
		write_xr(0x81, 0x14);		// 15 bit (555) color mode
		write_xr(0x82, 0x00);		// Disable palettes
		write_xr(0x20, 0x10);		// 16 bit blitter mode

		info->fix.line_length = 800*2;
		info->fix.visual = FB_VISUAL_TRUECOLOR;

		info->var.red.offset = 10;
		info->var.green.offset = 5;
		info->var.blue.offset = 0;
		info->var.red.length = info->var.green.length =
			info->var.blue.length = 5;
		
	} else {
		/* p->var.bits_per_pixel == 8 */
		write_cr(0x13, 100);		// Set line length (doublewords)
		write_xr(0x81, 0x12);		// 8 bit color mode
		write_xr(0x82, 0x08);		// Graphics gamma enable
		write_xr(0x20, 0x00);		// 8 bit blitter mode

		info->fix.line_length = 800;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;		

 		info->var.red.offset = info->var.green.offset =
			info->var.blue.offset = 0;
		info->var.red.length = info->var.green.length =
			info->var.blue.length = 8;
		
	}
	return 0;
}