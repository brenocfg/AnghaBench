#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct timespec {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_10__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  smps_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  work; } ;
struct sta_info {int* timer_to_tid; TYPE_5__ sta; int /*<<< orphan*/ * last_seq_ctrl; int /*<<< orphan*/ * tx_filtered; int /*<<< orphan*/ * ps_tx_buf; int /*<<< orphan*/  avg_signal; int /*<<< orphan*/  last_connected; int /*<<< orphan*/  sta_state; int /*<<< orphan*/  last_rx; struct ieee80211_sub_if_data* sdata; struct ieee80211_local* local; int /*<<< orphan*/  plink_timer; TYPE_2__ ampdu_mlme; int /*<<< orphan*/  drv_unblock_wk; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  user_mpm; } ;
struct TYPE_9__ {TYPE_3__ mesh; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; int /*<<< orphan*/  vif; struct ieee80211_local* local; } ;
struct TYPE_6__ {scalar_t__ sta_data_size; } ;
struct ieee80211_local {TYPE_1__ hw; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_NUM_ACS ; 
 int IEEE80211_NUM_TIDS ; 
 int /*<<< orphan*/  IEEE80211_SMPS_OFF ; 
 int /*<<< orphan*/  IEEE80211_STA_NONE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USHRT_MAX ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_posix_clock_monotonic_gettime (struct timespec*) ; 
 int /*<<< orphan*/  ewma_init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ieee80211_ba_session_work ; 
 scalar_t__ ieee80211_vif_is_mesh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct sta_info*) ; 
 struct sta_info* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sta_dbg (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sta_prepare_rate_control (struct ieee80211_local*,struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sta_unblock ; 

struct sta_info *sta_info_alloc(struct ieee80211_sub_if_data *sdata,
				const u8 *addr, gfp_t gfp)
{
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;
	struct timespec uptime;
	int i;

	sta = kzalloc(sizeof(*sta) + local->hw.sta_data_size, gfp);
	if (!sta)
		return NULL;

	spin_lock_init(&sta->lock);
	INIT_WORK(&sta->drv_unblock_wk, sta_unblock);
	INIT_WORK(&sta->ampdu_mlme.work, ieee80211_ba_session_work);
	mutex_init(&sta->ampdu_mlme.mtx);
#ifdef CONFIG_MAC80211_MESH
	if (ieee80211_vif_is_mesh(&sdata->vif) &&
	    !sdata->u.mesh.user_mpm)
		init_timer(&sta->plink_timer);
#endif

	memcpy(sta->sta.addr, addr, ETH_ALEN);
	sta->local = local;
	sta->sdata = sdata;
	sta->last_rx = jiffies;

	sta->sta_state = IEEE80211_STA_NONE;

	do_posix_clock_monotonic_gettime(&uptime);
	sta->last_connected = uptime.tv_sec;
	ewma_init(&sta->avg_signal, 1024, 8);

	if (sta_prepare_rate_control(local, sta, gfp)) {
		kfree(sta);
		return NULL;
	}

	for (i = 0; i < IEEE80211_NUM_TIDS; i++) {
		/*
		 * timer_to_tid must be initialized with identity mapping
		 * to enable session_timer's data differentiation. See
		 * sta_rx_agg_session_timer_expired for usage.
		 */
		sta->timer_to_tid[i] = i;
	}
	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		skb_queue_head_init(&sta->ps_tx_buf[i]);
		skb_queue_head_init(&sta->tx_filtered[i]);
	}

	for (i = 0; i < IEEE80211_NUM_TIDS; i++)
		sta->last_seq_ctrl[i] = cpu_to_le16(USHRT_MAX);

	sta->sta.smps_mode = IEEE80211_SMPS_OFF;

	sta_dbg(sdata, "Allocated STA %pM\n", sta->sta.addr);

	return sta;
}