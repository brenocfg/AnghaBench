#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ps; } ;
struct ieee80211_if_managed {int p2p_noa_index; int /*<<< orphan*/  req_smps; int /*<<< orphan*/  mtx; int /*<<< orphan*/  uapsd_max_sp_len; int /*<<< orphan*/  uapsd_queues; int /*<<< orphan*/  powersave; scalar_t__ flags; int /*<<< orphan*/  chswitch_timer; int /*<<< orphan*/  conn_mon_timer; int /*<<< orphan*/  bcn_mon_timer; int /*<<< orphan*/  timer; int /*<<< orphan*/  request_smps_work; int /*<<< orphan*/  csa_connection_drop_work; int /*<<< orphan*/  beacon_connection_loss_work; int /*<<< orphan*/  chswitch_work; int /*<<< orphan*/  monitor_work; } ;
struct TYPE_5__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_4__* local; TYPE_2__ wdev; TYPE_1__ u; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  uapsd_max_sp_len; int /*<<< orphan*/  uapsd_queues; } ;
struct TYPE_8__ {TYPE_3__ hw; } ;

/* Variables and functions */
 int IEEE80211_HW_SUPPORTS_DYNAMIC_SMPS ; 
 int /*<<< orphan*/  IEEE80211_SMPS_AUTOMATIC ; 
 int /*<<< orphan*/  IEEE80211_SMPS_OFF ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_beacon_connection_loss_work ; 
 int /*<<< orphan*/  ieee80211_chswitch_timer ; 
 int /*<<< orphan*/  ieee80211_chswitch_work ; 
 int /*<<< orphan*/  ieee80211_csa_connection_drop_work ; 
 int /*<<< orphan*/  ieee80211_request_smps_work ; 
 int /*<<< orphan*/  ieee80211_sta_bcn_mon_timer ; 
 int /*<<< orphan*/  ieee80211_sta_conn_mon_timer ; 
 int /*<<< orphan*/  ieee80211_sta_monitor_work ; 
 int /*<<< orphan*/  ieee80211_sta_timer ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

void ieee80211_sta_setup_sdata(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_managed *ifmgd;

	ifmgd = &sdata->u.mgd;
	INIT_WORK(&ifmgd->monitor_work, ieee80211_sta_monitor_work);
	INIT_WORK(&ifmgd->chswitch_work, ieee80211_chswitch_work);
	INIT_WORK(&ifmgd->beacon_connection_loss_work,
		  ieee80211_beacon_connection_loss_work);
	INIT_WORK(&ifmgd->csa_connection_drop_work,
		  ieee80211_csa_connection_drop_work);
	INIT_WORK(&ifmgd->request_smps_work, ieee80211_request_smps_work);
	setup_timer(&ifmgd->timer, ieee80211_sta_timer,
		    (unsigned long) sdata);
	setup_timer(&ifmgd->bcn_mon_timer, ieee80211_sta_bcn_mon_timer,
		    (unsigned long) sdata);
	setup_timer(&ifmgd->conn_mon_timer, ieee80211_sta_conn_mon_timer,
		    (unsigned long) sdata);
	setup_timer(&ifmgd->chswitch_timer, ieee80211_chswitch_timer,
		    (unsigned long) sdata);

	ifmgd->flags = 0;
	ifmgd->powersave = sdata->wdev.ps;
	ifmgd->uapsd_queues = sdata->local->hw.uapsd_queues;
	ifmgd->uapsd_max_sp_len = sdata->local->hw.uapsd_max_sp_len;
	ifmgd->p2p_noa_index = -1;

	mutex_init(&ifmgd->mtx);

	if (sdata->local->hw.flags & IEEE80211_HW_SUPPORTS_DYNAMIC_SMPS)
		ifmgd->req_smps = IEEE80211_SMPS_AUTOMATIC;
	else
		ifmgd->req_smps = IEEE80211_SMPS_OFF;
}