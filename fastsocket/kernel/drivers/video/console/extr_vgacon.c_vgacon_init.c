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
struct TYPE_2__ {int /*<<< orphan*/  height; } ;
struct vc_data {int vc_complement_mask; int vc_hi_font_mask; unsigned long* vc_uni_pagedir_loc; unsigned long vc_uni_pagedir; TYPE_1__ vc_font; int /*<<< orphan*/  vc_scan_lines; int /*<<< orphan*/  vc_rows; int /*<<< orphan*/  vc_cols; int /*<<< orphan*/  vc_can_do_color; } ;

/* Variables and functions */
 int /*<<< orphan*/  con_free_unimap (struct vc_data*) ; 
 int /*<<< orphan*/  con_set_default_unimap (struct vc_data*) ; 
 int /*<<< orphan*/  vc_resize (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vga_512_chars ; 
 int /*<<< orphan*/  vga_can_do_color ; 
 int /*<<< orphan*/  vga_scan_lines ; 
 int /*<<< orphan*/  vga_video_font_height ; 
 int /*<<< orphan*/  vga_video_num_columns ; 
 int /*<<< orphan*/  vga_video_num_lines ; 
 unsigned long* vgacon_uni_pagedir ; 

__attribute__((used)) static void vgacon_init(struct vc_data *c, int init)
{
	unsigned long p;

	/*
	 * We cannot be loaded as a module, therefore init is always 1,
	 * but vgacon_init can be called more than once, and init will
	 * not be 1.
	 */
	c->vc_can_do_color = vga_can_do_color;

	/* set dimensions manually if init != 0 since vc_resize() will fail */
	if (init) {
		c->vc_cols = vga_video_num_columns;
		c->vc_rows = vga_video_num_lines;
	} else
		vc_resize(c, vga_video_num_columns, vga_video_num_lines);

	c->vc_scan_lines = vga_scan_lines;
	c->vc_font.height = vga_video_font_height;
	c->vc_complement_mask = 0x7700;
	if (vga_512_chars)
		c->vc_hi_font_mask = 0x0800;
	p = *c->vc_uni_pagedir_loc;
	if (c->vc_uni_pagedir_loc == &c->vc_uni_pagedir ||
	    !--c->vc_uni_pagedir_loc[1])
		con_free_unimap(c);
	c->vc_uni_pagedir_loc = vgacon_uni_pagedir;
	vgacon_uni_pagedir[1]++;
	if (!vgacon_uni_pagedir[0] && p)
		con_set_default_unimap(c);
}