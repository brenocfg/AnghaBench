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
 int ENODEV ; 
 int /*<<< orphan*/  FBCON_LOGO_DONTSHOW ; 
 int* con2fb_map ; 
 int /*<<< orphan*/  fb_con ; 
 int fbcon_has_console_bind ; 
 int /*<<< orphan*/  fbcon_is_default ; 
 int first_fb_vc ; 
 int info_idx ; 
 int last_fb_vc ; 
 int /*<<< orphan*/  logo_shown ; 
 int /*<<< orphan*/  num_registered_fb ; 
 int take_over_console (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fbcon_takeover(int show_logo)
{
	int err, i;

	if (!num_registered_fb)
		return -ENODEV;

	if (!show_logo)
		logo_shown = FBCON_LOGO_DONTSHOW;

	for (i = first_fb_vc; i <= last_fb_vc; i++)
		con2fb_map[i] = info_idx;

	err = take_over_console(&fb_con, first_fb_vc, last_fb_vc,
				fbcon_is_default);

	if (err) {
		for (i = first_fb_vc; i <= last_fb_vc; i++) {
			con2fb_map[i] = -1;
		}
		info_idx = -1;
	} else {
		fbcon_has_console_bind = 1;
	}

	return err;
}