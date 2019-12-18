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
struct ieee80211_sub_if_data {int /*<<< orphan*/  crypto_tx_tailroom_needed_cnt; int /*<<< orphan*/  dec_tailroom_needed_wk; int /*<<< orphan*/  crypto_tx_tailroom_pending_dec; } ;
struct ieee80211_key {struct ieee80211_sub_if_data* sdata; scalar_t__ local; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ieee80211_debugfs_key_remove (struct ieee80211_key*) ; 
 int /*<<< orphan*/  ieee80211_key_disable_hw_accel (struct ieee80211_key*) ; 
 int /*<<< orphan*/  ieee80211_key_free_common (struct ieee80211_key*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void __ieee80211_key_destroy(struct ieee80211_key *key,
				    bool delay_tailroom)
{
	if (key->local)
		ieee80211_key_disable_hw_accel(key);

	if (key->local) {
		struct ieee80211_sub_if_data *sdata = key->sdata;

		ieee80211_debugfs_key_remove(key);

		if (delay_tailroom) {
			/* see ieee80211_delayed_tailroom_dec */
			sdata->crypto_tx_tailroom_pending_dec++;
			schedule_delayed_work(&sdata->dec_tailroom_needed_wk,
					      HZ/2);
		} else {
			sdata->crypto_tx_tailroom_needed_cnt--;
		}
	}

	ieee80211_key_free_common(key);
}