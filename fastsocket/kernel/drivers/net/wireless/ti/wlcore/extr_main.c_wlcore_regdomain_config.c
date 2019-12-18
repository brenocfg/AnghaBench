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
struct wl1271 {int quirks; scalar_t__ state; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int WLCORE_QUIRK_REGDOMAIN_CONF ; 
 scalar_t__ WLCORE_STATE_ON ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_ps_elp_sleep (struct wl1271*) ; 
 int wl1271_ps_elp_wakeup (struct wl1271*) ; 
 int /*<<< orphan*/  wl12xx_queue_recovery_work (struct wl1271*) ; 
 int wlcore_cmd_regdomain_config_locked (struct wl1271*) ; 

void wlcore_regdomain_config(struct wl1271 *wl)
{
	int ret;

	if (!(wl->quirks & WLCORE_QUIRK_REGDOMAIN_CONF))
		return;

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON))
		goto out;

	ret = wl1271_ps_elp_wakeup(wl);
	if (ret < 0)
		goto out;

	ret = wlcore_cmd_regdomain_config_locked(wl);
	if (ret < 0) {
		wl12xx_queue_recovery_work(wl);
		goto out;
	}

	wl1271_ps_elp_sleep(wl);
out:
	mutex_unlock(&wl->mutex);
}