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
struct ieee80211_low_level_stats {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct b43_wl {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ieee_stats; } ;

/* Variables and functions */
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_low_level_stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b43_op_get_stats(struct ieee80211_hw *hw,
			    struct ieee80211_low_level_stats *stats)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);

	mutex_lock(&wl->mutex);
	memcpy(stats, &wl->ieee_stats, sizeof(*stats));
	mutex_unlock(&wl->mutex);

	return 0;
}