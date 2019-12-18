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
struct TYPE_7__ {int /*<<< orphan*/  bc_buf; } ;
struct ieee80211_if_mesh {int /*<<< orphan*/  mesh_path_timer; int /*<<< orphan*/  mesh_path_root_timer; int /*<<< orphan*/  housekeeping_timer; TYPE_3__ ps; int /*<<< orphan*/  mtx; int /*<<< orphan*/  beacon; scalar_t__ mesh_id_len; } ;
struct TYPE_8__ {struct ieee80211_if_mesh mesh; } ;
struct TYPE_5__ {int enable_beacon; } ;
struct TYPE_6__ {TYPE_1__ bss_conf; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  work; TYPE_4__ u; int /*<<< orphan*/  state; TYPE_2__ vif; int /*<<< orphan*/  dev; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  iff_allmultis; int /*<<< orphan*/  fif_other_bss; int /*<<< orphan*/  total_ps_buffered; } ;
struct beacon_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_BEACON_ENABLED ; 
 int /*<<< orphan*/  SDATA_STATE_OFFCHANNEL_BEACON_STOPPED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_configure_filter (struct ieee80211_local*) ; 
 int /*<<< orphan*/  kfree_rcu (struct beacon_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_path_flush_by_iface (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct beacon_data* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sta_info_flush (struct ieee80211_sub_if_data*) ; 

void ieee80211_stop_mesh(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	struct beacon_data *bcn;

	netif_carrier_off(sdata->dev);

	/* stop the beacon */
	ifmsh->mesh_id_len = 0;
	sdata->vif.bss_conf.enable_beacon = false;
	clear_bit(SDATA_STATE_OFFCHANNEL_BEACON_STOPPED, &sdata->state);
	ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BEACON_ENABLED);
	mutex_lock(&ifmsh->mtx);
	bcn = rcu_dereference_protected(ifmsh->beacon,
					lockdep_is_held(&ifmsh->mtx));
	rcu_assign_pointer(ifmsh->beacon, NULL);
	kfree_rcu(bcn, rcu_head);
	mutex_unlock(&ifmsh->mtx);

	/* flush STAs and mpaths on this iface */
	sta_info_flush(sdata);
	mesh_path_flush_by_iface(sdata);

	/* free all potentially still buffered group-addressed frames */
	local->total_ps_buffered -= skb_queue_len(&ifmsh->ps.bc_buf);
	skb_queue_purge(&ifmsh->ps.bc_buf);

	del_timer_sync(&sdata->u.mesh.housekeeping_timer);
	del_timer_sync(&sdata->u.mesh.mesh_path_root_timer);
	del_timer_sync(&sdata->u.mesh.mesh_path_timer);
	/*
	 * If the timer fired while we waited for it, it will have
	 * requeued the work. Now the work will be running again
	 * but will not rearm the timer again because it checks
	 * whether the interface is running, which, at this point,
	 * it no longer is.
	 */
	cancel_work_sync(&sdata->work);

	local->fif_other_bss--;
	atomic_dec(&local->iff_allmultis);
	ieee80211_configure_filter(local);
}