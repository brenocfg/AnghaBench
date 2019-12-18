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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int add_has_run; int /*<<< orphan*/  dir; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_2__ debugfs; TYPE_3__ sta; struct ieee80211_sub_if_data* sdata; struct ieee80211_local* local; } ;
struct TYPE_4__ {struct dentry* subdir_stations; } ;
struct ieee80211_sub_if_data {TYPE_1__ debugfs; } ;
struct ieee80211_local {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  mac ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGFS_ADD_COUNTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  agg_status ; 
 int /*<<< orphan*/  beacon_loss_count ; 
 int /*<<< orphan*/  connected_time ; 
 int /*<<< orphan*/  current_tx_rate ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ *,struct dentry*) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  drv_sta_add_debugfs (struct ieee80211_local*,struct ieee80211_sub_if_data*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  ht_capa ; 
 int /*<<< orphan*/  inactive_ms ; 
 int /*<<< orphan*/  last_ack_signal ; 
 int /*<<< orphan*/  last_rx_rate ; 
 int /*<<< orphan*/  last_seq_ctrl ; 
 int /*<<< orphan*/  last_signal ; 
 int /*<<< orphan*/  num_duplicates ; 
 int /*<<< orphan*/  num_ps_buf_frames ; 
 int /*<<< orphan*/  rx_bytes ; 
 int /*<<< orphan*/  rx_dropped ; 
 int /*<<< orphan*/  rx_duplicates ; 
 int /*<<< orphan*/  rx_fragments ; 
 int /*<<< orphan*/  rx_packets ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_bytes ; 
 int /*<<< orphan*/  tx_filtered ; 
 int /*<<< orphan*/  tx_filtered_count ; 
 int /*<<< orphan*/  tx_fragments ; 
 int /*<<< orphan*/  tx_packets ; 
 int /*<<< orphan*/  tx_retry_count ; 
 int /*<<< orphan*/  tx_retry_failed ; 
 int /*<<< orphan*/  vht_capa ; 
 int /*<<< orphan*/  wep_weak_iv_count ; 

void ieee80211_sta_debugfs_add(struct sta_info *sta)
{
	struct ieee80211_local *local = sta->local;
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct dentry *stations_dir = sta->sdata->debugfs.subdir_stations;
	u8 mac[3*ETH_ALEN];

	sta->debugfs.add_has_run = true;

	if (!stations_dir)
		return;

	snprintf(mac, sizeof(mac), "%pM", sta->sta.addr);

	/*
	 * This might fail due to a race condition:
	 * When mac80211 unlinks a station, the debugfs entries
	 * remain, but it is already possible to link a new
	 * station with the same address which triggers adding
	 * it to debugfs; therefore, if the old station isn't
	 * destroyed quickly enough the old station's debugfs
	 * dir might still be around.
	 */
	sta->debugfs.dir = debugfs_create_dir(mac, stations_dir);
	if (!sta->debugfs.dir)
		return;

	DEBUGFS_ADD(flags);
	DEBUGFS_ADD(num_ps_buf_frames);
	DEBUGFS_ADD(inactive_ms);
	DEBUGFS_ADD(connected_time);
	DEBUGFS_ADD(last_seq_ctrl);
	DEBUGFS_ADD(agg_status);
	DEBUGFS_ADD(dev);
	DEBUGFS_ADD(last_signal);
	DEBUGFS_ADD(beacon_loss_count);
	DEBUGFS_ADD(ht_capa);
	DEBUGFS_ADD(vht_capa);
	DEBUGFS_ADD(last_ack_signal);
	DEBUGFS_ADD(current_tx_rate);
	DEBUGFS_ADD(last_rx_rate);

	DEBUGFS_ADD_COUNTER(rx_packets, rx_packets);
	DEBUGFS_ADD_COUNTER(tx_packets, tx_packets);
	DEBUGFS_ADD_COUNTER(rx_bytes, rx_bytes);
	DEBUGFS_ADD_COUNTER(tx_bytes, tx_bytes);
	DEBUGFS_ADD_COUNTER(rx_duplicates, num_duplicates);
	DEBUGFS_ADD_COUNTER(rx_fragments, rx_fragments);
	DEBUGFS_ADD_COUNTER(rx_dropped, rx_dropped);
	DEBUGFS_ADD_COUNTER(tx_fragments, tx_fragments);
	DEBUGFS_ADD_COUNTER(tx_filtered, tx_filtered_count);
	DEBUGFS_ADD_COUNTER(tx_retry_failed, tx_retry_failed);
	DEBUGFS_ADD_COUNTER(tx_retry_count, tx_retry_count);
	DEBUGFS_ADD_COUNTER(wep_weak_iv_count, wep_weak_iv_count);

	drv_sta_add_debugfs(local, sdata, &sta->sta, sta->debugfs.dir);
}