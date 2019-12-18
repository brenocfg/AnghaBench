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

/* Variables and functions */
 int PAHW_32X ; 
 int PicoAHW ; 
 int /*<<< orphan*/  change_renderer (int) ; 
 int /*<<< orphan*/  emu_status_msg (int /*<<< orphan*/ ) ; 
 size_t get_renderer () ; 
 int /*<<< orphan*/ * renderer_names ; 
 int /*<<< orphan*/ * renderer_names32x ; 
 int rendstatus_old ; 
 int /*<<< orphan*/  vid_reset_mode () ; 

void plat_video_toggle_renderer(int change, int is_menu_call)
{
	change_renderer(change);

	if (is_menu_call)
		return;

	vid_reset_mode();
	rendstatus_old = -1;

	if (PicoAHW & PAHW_32X)
		emu_status_msg(renderer_names32x[get_renderer()]);
	else
		emu_status_msg(renderer_names[get_renderer()]);
}