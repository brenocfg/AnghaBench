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
struct vc_data {scalar_t__ vc_mode; int /*<<< orphan*/  vc_num; TYPE_1__* vc_sw; } ;
struct TYPE_4__ {struct vc_data* d; } ;
struct TYPE_3__ {scalar_t__ (* con_blank ) (struct vc_data*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ KD_TEXT ; 
 int /*<<< orphan*/  VT_EVENT_UNBLANK ; 
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int /*<<< orphan*/  blank_normal_wait ; 
 int /*<<< orphan*/  blank_state ; 
 int blankinterval ; 
 int /*<<< orphan*/  console_blank_hook (int /*<<< orphan*/ ) ; 
 scalar_t__ console_blanked ; 
 int /*<<< orphan*/  console_timer ; 
 int fg_console ; 
 scalar_t__ ignore_poke ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  oops_in_progress ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  set_cursor (struct vc_data*) ; 
 int /*<<< orphan*/  set_palette (struct vc_data*) ; 
 scalar_t__ stub1 (struct vc_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_screen (struct vc_data*) ; 
 TYPE_2__* vc_cons ; 
 int /*<<< orphan*/  vc_cons_allocated (int) ; 
 int /*<<< orphan*/  vt_event_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vt_force_oops_output (struct vc_data*) ; 

void do_unblank_screen(int leaving_gfx)
{
	struct vc_data *vc;

	/* This should now always be called from a "sane" (read: can schedule)
	 * context for the sake of the low level drivers, except in the special
	 * case of oops_in_progress
	 */
	if (!oops_in_progress)
		might_sleep();

	WARN_CONSOLE_UNLOCKED();

	ignore_poke = 0;
	if (!console_blanked)
		return;
	if (!vc_cons_allocated(fg_console)) {
		/* impossible */
		printk("unblank_screen: tty %d not allocated ??\n", fg_console+1);
		return;
	}
	vc = vc_cons[fg_console].d;
	/* Try to unblank in oops case too */
	if (vc->vc_mode != KD_TEXT && !vt_force_oops_output(vc))
		return; /* but leave console_blanked != 0 */

	if (blankinterval) {
		mod_timer(&console_timer, jiffies + (blankinterval * HZ));
		blank_state = blank_normal_wait;
	}

	console_blanked = 0;
	if (vc->vc_sw->con_blank(vc, 0, leaving_gfx) || vt_force_oops_output(vc))
		/* Low-level driver cannot restore -> do it ourselves */
		update_screen(vc);
	if (console_blank_hook)
		console_blank_hook(0);
	set_palette(vc);
	set_cursor(vc);
	vt_event_post(VT_EVENT_UNBLANK, vc->vc_num, vc->vc_num);
}