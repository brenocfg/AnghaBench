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
struct ieee80211_roc_work {int notified; int /*<<< orphan*/  req_duration; TYPE_2__* chan; int /*<<< orphan*/  cookie; TYPE_1__* sdata; int /*<<< orphan*/ * frame; scalar_t__ mgmt_tx_cookie; } ;
struct TYPE_4__ {int /*<<< orphan*/  band; } ;
struct TYPE_3__ {int /*<<< orphan*/  wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cfg80211_ready_on_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_skb_tid_band (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void ieee80211_handle_roc_started(struct ieee80211_roc_work *roc)
{
	if (roc->notified)
		return;

	if (roc->mgmt_tx_cookie) {
		if (!WARN_ON(!roc->frame)) {
			ieee80211_tx_skb_tid_band(roc->sdata, roc->frame, 7,
						  roc->chan->band);
			roc->frame = NULL;
		}
	} else {
		cfg80211_ready_on_channel(&roc->sdata->wdev, roc->cookie,
					  roc->chan, roc->req_duration,
					  GFP_KERNEL);
	}

	roc->notified = true;
}