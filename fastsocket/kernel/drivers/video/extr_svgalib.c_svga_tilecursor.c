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
typedef  int u8 ;
typedef  int u16 ;
struct fb_tilecursor {int sx; int sy; int shape; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int xoffset; int yoffset; int xres_virtual; } ;
struct fb_info {TYPE_1__ var; } ;

/* Variables and functions */
#define  FB_TILE_CURSOR_BLOCK 132 
#define  FB_TILE_CURSOR_LOWER_HALF 131 
#define  FB_TILE_CURSOR_LOWER_THIRD 130 
 int FB_TILE_CURSOR_NONE ; 
#define  FB_TILE_CURSOR_TWO_THIRDS 129 
#define  FB_TILE_CURSOR_UNDERLINE 128 
 int /*<<< orphan*/  svga_wcrt_mask (int,int,int) ; 
 int /*<<< orphan*/  vga_wcrt (int /*<<< orphan*/ *,int,int) ; 

void svga_tilecursor(struct fb_info *info, struct fb_tilecursor *cursor)
{
	u8 cs = 0x0d;
	u8 ce = 0x0e;
	u16 pos =  cursor->sx + (info->var.xoffset /  8)
		+ (cursor->sy + (info->var.yoffset / 16))
		   * (info->var.xres_virtual / 8);

	if (! cursor -> mode)
		return;

	svga_wcrt_mask(0x0A, 0x20, 0x20); /* disable cursor */

	if (cursor -> shape == FB_TILE_CURSOR_NONE)
		return;

	switch (cursor -> shape) {
	case FB_TILE_CURSOR_UNDERLINE:
		cs = 0x0d;
		break;
	case FB_TILE_CURSOR_LOWER_THIRD:
		cs = 0x09;
		break;
	case FB_TILE_CURSOR_LOWER_HALF:
		cs = 0x07;
		break;
	case FB_TILE_CURSOR_TWO_THIRDS:
		cs = 0x05;
		break;
	case FB_TILE_CURSOR_BLOCK:
		cs = 0x01;
		break;
	}

	/* set cursor position */
	vga_wcrt(NULL, 0x0E, pos >> 8);
	vga_wcrt(NULL, 0x0F, pos & 0xFF);

	vga_wcrt(NULL, 0x0B, ce); /* set cursor end */
	vga_wcrt(NULL, 0x0A, cs); /* set cursor start and enable it */
}