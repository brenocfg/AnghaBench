#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int vc_num; int vc_complement_mask; int vc_panic_force_write; int vc_s_complement_mask; int vc_size_row; int vc_cols; int vc_screenbuf_size; int vc_rows; scalar_t__ vc_can_do_color; TYPE_1__* vc_sw; scalar_t__ vc_hi_font_mask; scalar_t__ vc_uni_pagedir; scalar_t__* vc_uni_pagedir_loc; int /*<<< orphan*/ * vc_display_fg; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* con_init ) (struct vc_data*,int) ;int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 TYPE_1__** con_driver_map ; 
 TYPE_1__* conswitchp ; 
 int /*<<< orphan*/  master_display_fg ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,int) ; 

__attribute__((used)) static void visual_init(struct vc_data *vc, int num, int init)
{
	/* ++Geert: vc->vc_sw->con_init determines console size */
	if (vc->vc_sw)
		module_put(vc->vc_sw->owner);
	vc->vc_sw = conswitchp;
#ifndef VT_SINGLE_DRIVER
	if (con_driver_map[num])
		vc->vc_sw = con_driver_map[num];
#endif
	__module_get(vc->vc_sw->owner);
	vc->vc_num = num;
	vc->vc_display_fg = &master_display_fg;
	vc->vc_uni_pagedir_loc = &vc->vc_uni_pagedir;
	vc->vc_uni_pagedir = 0;
	vc->vc_hi_font_mask = 0;
	vc->vc_complement_mask = 0;
	vc->vc_can_do_color = 0;
	vc->vc_panic_force_write = false;
	vc->vc_sw->con_init(vc, init);
	if (!vc->vc_complement_mask)
		vc->vc_complement_mask = vc->vc_can_do_color ? 0x7700 : 0x0800;
	vc->vc_s_complement_mask = vc->vc_complement_mask;
	vc->vc_size_row = vc->vc_cols << 1;
	vc->vc_screenbuf_size = vc->vc_rows * vc->vc_size_row;
}