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
struct vc_data {int dummy; } ;
struct fb_info {int dummy; } ;
struct TYPE_2__ {struct vc_data* d; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FBCON_LOGO_DONTSHOW ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 int con2fb_acquire_newinfo (struct vc_data*,struct fb_info*,int,int) ; 
 int /*<<< orphan*/  con2fb_init_display (struct vc_data*,struct fb_info*,int,int) ; 
 int* con2fb_map ; 
 int* con2fb_map_boot ; 
 int con2fb_release_oldinfo (struct vc_data*,struct fb_info*,struct fb_info*,int,int,int) ; 
 int /*<<< orphan*/  con_is_bound (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_con ; 
 int /*<<< orphan*/  fbcon_add_cursor_timer (struct fb_info*) ; 
 int fbcon_takeover (int /*<<< orphan*/ ) ; 
 scalar_t__ fg_console ; 
 int info_idx ; 
 scalar_t__ logo_shown ; 
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  release_console_sem () ; 
 int search_fb_in_map (int) ; 
 int /*<<< orphan*/  search_for_mapped_con () ; 
 TYPE_1__* vc_cons ; 

__attribute__((used)) static int set_con2fb_map(int unit, int newidx, int user)
{
	struct vc_data *vc = vc_cons[unit].d;
	int oldidx = con2fb_map[unit];
	struct fb_info *info = registered_fb[newidx];
	struct fb_info *oldinfo = NULL;
 	int found, err = 0;

	if (oldidx == newidx)
		return 0;

	if (!info)
		return -EINVAL;

	if (!search_for_mapped_con() || !con_is_bound(&fb_con)) {
		info_idx = newidx;
		return fbcon_takeover(0);
	}

	if (oldidx != -1)
		oldinfo = registered_fb[oldidx];

	found = search_fb_in_map(newidx);

	acquire_console_sem();
	con2fb_map[unit] = newidx;
	if (!err && !found)
 		err = con2fb_acquire_newinfo(vc, info, unit, oldidx);


	/*
	 * If old fb is not mapped to any of the consoles,
	 * fbcon should release it.
	 */
 	if (!err && oldinfo && !search_fb_in_map(oldidx))
 		err = con2fb_release_oldinfo(vc, oldinfo, info, unit, oldidx,
 					     found);

 	if (!err) {
 		int show_logo = (fg_console == 0 && !user &&
 				 logo_shown != FBCON_LOGO_DONTSHOW);

 		if (!found)
 			fbcon_add_cursor_timer(info);
 		con2fb_map_boot[unit] = newidx;
 		con2fb_init_display(vc, info, unit, show_logo);
	}

	if (!search_fb_in_map(info_idx))
		info_idx = newidx;

	release_console_sem();
 	return err;
}