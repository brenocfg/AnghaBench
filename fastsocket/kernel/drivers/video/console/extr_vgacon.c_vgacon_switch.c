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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int height; } ;
struct vc_data {int vc_cols; int vc_rows; scalar_t__ vc_screenbuf_size; int /*<<< orphan*/  vc_size_row; scalar_t__ vc_screenbuf; scalar_t__ vc_origin; TYPE_1__ vc_font; } ;
struct TYPE_4__ {int orig_video_lines; int orig_video_cols; } ;

/* Variables and functions */
 int VGA_FONTWIDTH ; 
 int /*<<< orphan*/  scr_memcpyw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__ screen_info ; 
 int vga_default_font_height ; 
 int /*<<< orphan*/  vga_is_gfx ; 
 int vga_video_num_columns ; 
 int vga_video_num_lines ; 
 scalar_t__ vga_vram_size ; 
 int /*<<< orphan*/  vgacon_doresize (struct vc_data*,int,int) ; 
 int /*<<< orphan*/  vgacon_scrollback_init (int /*<<< orphan*/ ) ; 
 int vgacon_xres ; 
 int vgacon_yres ; 

__attribute__((used)) static int vgacon_switch(struct vc_data *c)
{
	int x = c->vc_cols * VGA_FONTWIDTH;
	int y = c->vc_rows * c->vc_font.height;
	int rows = screen_info.orig_video_lines * vga_default_font_height/
		c->vc_font.height;
	/*
	 * We need to save screen size here as it's the only way
	 * we can spot the screen has been resized and we need to
	 * set size of freshly allocated screens ourselves.
	 */
	vga_video_num_columns = c->vc_cols;
	vga_video_num_lines = c->vc_rows;

	/* We can only copy out the size of the video buffer here,
	 * otherwise we get into VGA BIOS */

	if (!vga_is_gfx) {
		scr_memcpyw((u16 *) c->vc_origin, (u16 *) c->vc_screenbuf,
			    c->vc_screenbuf_size > vga_vram_size ?
				vga_vram_size : c->vc_screenbuf_size);

		if ((vgacon_xres != x || vgacon_yres != y) &&
		    (!(vga_video_num_columns % 2) &&
		     vga_video_num_columns <= screen_info.orig_video_cols &&
		     vga_video_num_lines <= rows))
			vgacon_doresize(c, c->vc_cols, c->vc_rows);
	}

	vgacon_scrollback_init(c->vc_size_row);
	return 0;		/* Redrawing not needed */
}