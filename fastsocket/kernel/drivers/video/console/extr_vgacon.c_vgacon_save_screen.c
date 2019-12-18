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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {scalar_t__ vc_screenbuf_size; scalar_t__ vc_origin; scalar_t__ vc_screenbuf; int /*<<< orphan*/  vc_y; int /*<<< orphan*/  vc_x; } ;
struct TYPE_2__ {int /*<<< orphan*/  orig_y; int /*<<< orphan*/  orig_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  scr_memcpyw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ screen_info ; 
 int /*<<< orphan*/  vga_is_gfx ; 
 scalar_t__ vga_vram_size ; 

__attribute__((used)) static void vgacon_save_screen(struct vc_data *c)
{
	static int vga_bootup_console = 0;

	if (!vga_bootup_console) {
		/* This is a gross hack, but here is the only place we can
		 * set bootup console parameters without messing up generic
		 * console initialization routines.
		 */
		vga_bootup_console = 1;
		c->vc_x = screen_info.orig_x;
		c->vc_y = screen_info.orig_y;
	}

	/* We can't copy in more than the size of the video buffer,
	 * or we'll be copying in VGA BIOS */

	if (!vga_is_gfx)
		scr_memcpyw((u16 *) c->vc_screenbuf, (u16 *) c->vc_origin,
			    c->vc_screenbuf_size > vga_vram_size ? vga_vram_size : c->vc_screenbuf_size);
}