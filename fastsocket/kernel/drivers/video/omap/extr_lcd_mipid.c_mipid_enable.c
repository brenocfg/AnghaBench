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
struct mipid_device {int enabled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  saved_bklight_level; } ;
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mipid_esd_start_check (struct mipid_device*) ; 
 int /*<<< orphan*/  mipid_set_bklight_level (struct lcd_panel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_init_string (struct mipid_device*) ; 
 int /*<<< orphan*/  set_display_state (struct mipid_device*,int) ; 
 int /*<<< orphan*/  set_sleep_mode (struct mipid_device*,int /*<<< orphan*/ ) ; 
 struct mipid_device* to_mipid_device (struct lcd_panel*) ; 

__attribute__((used)) static int mipid_enable(struct lcd_panel *panel)
{
	struct mipid_device *md = to_mipid_device(panel);

	mutex_lock(&md->mutex);

	if (md->enabled) {
		mutex_unlock(&md->mutex);
		return 0;
	}
	set_sleep_mode(md, 0);
	md->enabled = 1;
	send_init_string(md);
	set_display_state(md, 1);
	mipid_set_bklight_level(panel, md->saved_bklight_level);
	mipid_esd_start_check(md);

	mutex_unlock(&md->mutex);
	return 0;
}