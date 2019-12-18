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
struct wl1271 {int /*<<< orphan*/  mutex; } ;
struct ieee80211_hw {struct wl1271* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wlcore_op_stop_locked (struct wl1271*) ; 

__attribute__((used)) static void wlcore_op_stop(struct ieee80211_hw *hw)
{
	struct wl1271 *wl = hw->priv;

	wl1271_debug(DEBUG_MAC80211, "mac80211 stop");

	mutex_lock(&wl->mutex);

	wlcore_op_stop_locked(wl);

	mutex_unlock(&wl->mutex);
}