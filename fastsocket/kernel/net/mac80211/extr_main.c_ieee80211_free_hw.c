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
struct TYPE_3__ {TYPE_2__* wiphy; } ;
struct ieee80211_local {TYPE_1__ hw; int /*<<< orphan*/  ack_status_frames; scalar_t__ wiphy_ciphers_allocated; int /*<<< orphan*/  mtx; int /*<<< orphan*/  iflist_mtx; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cipher_suites; } ;

/* Variables and functions */
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_ack_frame ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_free (TYPE_2__*) ; 

void ieee80211_free_hw(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	mutex_destroy(&local->iflist_mtx);
	mutex_destroy(&local->mtx);

	if (local->wiphy_ciphers_allocated)
		kfree(local->hw.wiphy->cipher_suites);

	idr_for_each(&local->ack_status_frames,
		     ieee80211_free_ack_frame, NULL);
	idr_destroy(&local->ack_status_frames);

	wiphy_free(local->hw.wiphy);
}