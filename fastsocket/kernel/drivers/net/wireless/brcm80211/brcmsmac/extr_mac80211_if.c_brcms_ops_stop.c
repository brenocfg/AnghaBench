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
struct ieee80211_hw {struct brcms_info* priv; } ;
struct brcms_info {int /*<<< orphan*/  lock; TYPE_2__* wlc; } ;
struct TYPE_4__ {TYPE_1__* hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 int brcms_c_chipmatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_down (struct brcms_info*) ; 
 int /*<<< orphan*/  brcms_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcms_ops_stop(struct ieee80211_hw *hw)
{
	struct brcms_info *wl = hw->priv;
	int status;

	ieee80211_stop_queues(hw);

	if (wl->wlc == NULL)
		return;

	spin_lock_bh(&wl->lock);
	status = brcms_c_chipmatch(wl->wlc->hw->d11core);
	spin_unlock_bh(&wl->lock);
	if (!status) {
		brcms_err(wl->wlc->hw->d11core,
			  "wl: brcms_ops_stop: chipmatch failed\n");
		return;
	}

	/* put driver in down state */
	spin_lock_bh(&wl->lock);
	brcms_down(wl);
	spin_unlock_bh(&wl->lock);
}