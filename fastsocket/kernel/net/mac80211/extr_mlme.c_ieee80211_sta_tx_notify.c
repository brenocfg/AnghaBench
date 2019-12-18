#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ probe_send_count; int nullfunc_failed; } ;
struct TYPE_5__ {TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  work; TYPE_3__* local; TYPE_2__ u; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_sta_reset_conn_monitor (struct ieee80211_sub_if_data*) ; 

void ieee80211_sta_tx_notify(struct ieee80211_sub_if_data *sdata,
			     struct ieee80211_hdr *hdr, bool ack)
{
	if (!ieee80211_is_data(hdr->frame_control))
	    return;

	if (ieee80211_is_nullfunc(hdr->frame_control) &&
	    sdata->u.mgd.probe_send_count > 0) {
		if (ack)
			ieee80211_sta_reset_conn_monitor(sdata);
		else
			sdata->u.mgd.nullfunc_failed = true;
		ieee80211_queue_work(&sdata->local->hw, &sdata->work);
		return;
	}

	if (ack)
		ieee80211_sta_reset_conn_monitor(sdata);
}