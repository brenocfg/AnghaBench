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
struct il_priv {struct ieee80211_vif* scan_vif; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  il_force_scan_end (struct il_priv*) ; 
 int /*<<< orphan*/  il_scan_cancel_timeout (struct il_priv*,int) ; 
 int /*<<< orphan*/  il_set_mode (struct il_priv*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il_teardown_interface(struct il_priv *il, struct ieee80211_vif *vif)
{
	lockdep_assert_held(&il->mutex);

	if (il->scan_vif == vif) {
		il_scan_cancel_timeout(il, 200);
		il_force_scan_end(il);
	}

	il_set_mode(il);
}