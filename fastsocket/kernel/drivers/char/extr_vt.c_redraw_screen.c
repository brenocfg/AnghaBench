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
struct vc_data {size_t vc_num; int vc_can_do_color; scalar_t__ vc_mode; int vc_screenbuf_size; int /*<<< orphan*/  vc_origin; TYPE_1__* vc_sw; struct vc_data** vc_display_fg; } ;
struct TYPE_4__ {struct vc_data* d; } ;
struct TYPE_3__ {int (* con_switch ) (struct vc_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CON_IS_VISIBLE (struct vc_data*) ; 
 scalar_t__ KD_GRAPHICS ; 
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int /*<<< orphan*/  clear_buffer_attributes (struct vc_data*) ; 
 int /*<<< orphan*/  compute_shiftstate () ; 
 int /*<<< orphan*/  do_update_region (struct vc_data*,int /*<<< orphan*/ ,int) ; 
 size_t fg_console ; 
 int /*<<< orphan*/  hide_cursor (struct vc_data*) ; 
 int /*<<< orphan*/  notify_update (struct vc_data*) ; 
 int /*<<< orphan*/  save_screen (struct vc_data*) ; 
 int /*<<< orphan*/  set_cursor (struct vc_data*) ; 
 int /*<<< orphan*/  set_leds () ; 
 int /*<<< orphan*/  set_origin (struct vc_data*) ; 
 int /*<<< orphan*/  set_palette (struct vc_data*) ; 
 int stub1 (struct vc_data*) ; 
 int /*<<< orphan*/  update_attr (struct vc_data*) ; 
 TYPE_2__* vc_cons ; 
 scalar_t__ vt_force_oops_output (struct vc_data*) ; 

void redraw_screen(struct vc_data *vc, int is_switch)
{
	int redraw = 0;

	WARN_CONSOLE_UNLOCKED();

	if (!vc) {
		/* strange ... */
		/* printk("redraw_screen: tty %d not allocated ??\n", new_console+1); */
		return;
	}

	if (is_switch) {
		struct vc_data *old_vc = vc_cons[fg_console].d;
		if (old_vc == vc)
			return;
		if (!CON_IS_VISIBLE(vc))
			redraw = 1;
		*vc->vc_display_fg = vc;
		fg_console = vc->vc_num;
		hide_cursor(old_vc);
		if (!CON_IS_VISIBLE(old_vc)) {
			save_screen(old_vc);
			set_origin(old_vc);
		}
	} else {
		hide_cursor(vc);
		redraw = 1;
	}

	if (redraw) {
		int update;
		int old_was_color = vc->vc_can_do_color;

		set_origin(vc);
		update = vc->vc_sw->con_switch(vc);
		set_palette(vc);
		/*
		 * If console changed from mono<->color, the best we can do
		 * is to clear the buffer attributes. As it currently stands,
		 * rebuilding new attributes from the old buffer is not doable
		 * without overly complex code.
		 */
		if (old_was_color != vc->vc_can_do_color) {
			update_attr(vc);
			clear_buffer_attributes(vc);
		}

		/* Forcibly update if we're panicing */
		if ((update && vc->vc_mode != KD_GRAPHICS) ||
		    vt_force_oops_output(vc))
			do_update_region(vc, vc->vc_origin, vc->vc_screenbuf_size / 2);
	}
	set_cursor(vc);
	if (is_switch) {
		set_leds();
		compute_shiftstate();
		notify_update(vc);
	}
}