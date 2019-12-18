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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct sta_info {int dummy; } ;
struct mesh_path {scalar_t__ sn; scalar_t__ rann_metric; int flags; int is_root; int /*<<< orphan*/  rann_snd_addr; scalar_t__ last_preq_to_root; } ;
struct TYPE_8__ {scalar_t__ dot11MeshForwarding; } ;
struct TYPE_7__ {int /*<<< orphan*/  dropped_frames_ttl; int /*<<< orphan*/  dropped_frames_no_route; } ;
struct ieee80211_if_mesh {TYPE_4__ mshcfg; TYPE_3__ mshstats; } ;
struct TYPE_6__ {struct ieee80211_if_mesh mesh; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; TYPE_1__ vif; struct ieee80211_local* local; } ;
struct ieee80211_rann_ie {int rann_ttl; int rann_flags; int* rann_addr; int rann_hopcount; int /*<<< orphan*/  rann_metric; int /*<<< orphan*/  rann_interval; int /*<<< orphan*/  rann_seq; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  sa; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ IS_ERR (struct mesh_path*) ; 
 int MESH_PATH_ACTIVE ; 
 int MESH_PATH_FIXED ; 
 int MESH_PATH_RESOLVING ; 
 int /*<<< orphan*/  MPATH_RANN ; 
 int PREQ_Q_F_REFRESH ; 
 int PREQ_Q_F_START ; 
 int RANN_FLAG_IS_GATE ; 
 int /*<<< orphan*/  SN_LT (scalar_t__,scalar_t__) ; 
 scalar_t__ airtime_link_metric_get (struct ieee80211_local*,struct sta_info*) ; 
 int /*<<< orphan*/  broadcast_addr ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 scalar_t__ ether_addr_equal (int const*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mesh_path* mesh_path_add (struct ieee80211_sub_if_data*,int const*) ; 
 int /*<<< orphan*/  mesh_path_add_gate (struct mesh_path*) ; 
 struct mesh_path* mesh_path_lookup (struct ieee80211_sub_if_data*,int const*) ; 
 int /*<<< orphan*/  mesh_path_sel_frame_tx (int /*<<< orphan*/ ,int,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mesh_queue_preq (struct mesh_path*,int) ; 
 int /*<<< orphan*/  mhwmp_dbg (struct ieee80211_sub_if_data*,char*,int const*,...) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ root_path_confirmation_jiffies (struct ieee80211_sub_if_data*) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void hwmp_rann_frame_process(struct ieee80211_sub_if_data *sdata,
				    struct ieee80211_mgmt *mgmt,
				    const struct ieee80211_rann_ie *rann)
{
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;
	struct mesh_path *mpath;
	u8 ttl, flags, hopcount;
	const u8 *orig_addr;
	u32 orig_sn, metric, metric_txsta, interval;
	bool root_is_gate;

	ttl = rann->rann_ttl;
	flags = rann->rann_flags;
	root_is_gate = !!(flags & RANN_FLAG_IS_GATE);
	orig_addr = rann->rann_addr;
	orig_sn = le32_to_cpu(rann->rann_seq);
	interval = le32_to_cpu(rann->rann_interval);
	hopcount = rann->rann_hopcount;
	hopcount++;
	metric = le32_to_cpu(rann->rann_metric);

	/*  Ignore our own RANNs */
	if (ether_addr_equal(orig_addr, sdata->vif.addr))
		return;

	mhwmp_dbg(sdata,
		  "received RANN from %pM via neighbour %pM (is_gate=%d)\n",
		  orig_addr, mgmt->sa, root_is_gate);

	rcu_read_lock();
	sta = sta_info_get(sdata, mgmt->sa);
	if (!sta) {
		rcu_read_unlock();
		return;
	}

	metric_txsta = airtime_link_metric_get(local, sta);

	mpath = mesh_path_lookup(sdata, orig_addr);
	if (!mpath) {
		mpath = mesh_path_add(sdata, orig_addr);
		if (IS_ERR(mpath)) {
			rcu_read_unlock();
			sdata->u.mesh.mshstats.dropped_frames_no_route++;
			return;
		}
	}

	if (!(SN_LT(mpath->sn, orig_sn)) &&
	    !(mpath->sn == orig_sn && metric < mpath->rann_metric)) {
		rcu_read_unlock();
		return;
	}

	if ((!(mpath->flags & (MESH_PATH_ACTIVE | MESH_PATH_RESOLVING)) ||
	     (time_after(jiffies, mpath->last_preq_to_root +
				  root_path_confirmation_jiffies(sdata)) ||
	     time_before(jiffies, mpath->last_preq_to_root))) &&
	     !(mpath->flags & MESH_PATH_FIXED) && (ttl != 0)) {
		mhwmp_dbg(sdata,
			  "time to refresh root mpath %pM\n",
			  orig_addr);
		mesh_queue_preq(mpath, PREQ_Q_F_START | PREQ_Q_F_REFRESH);
		mpath->last_preq_to_root = jiffies;
	}

	mpath->sn = orig_sn;
	mpath->rann_metric = metric + metric_txsta;
	mpath->is_root = true;
	/* Recording RANNs sender address to send individually
	 * addressed PREQs destined for root mesh STA */
	memcpy(mpath->rann_snd_addr, mgmt->sa, ETH_ALEN);

	if (root_is_gate)
		mesh_path_add_gate(mpath);

	if (ttl <= 1) {
		ifmsh->mshstats.dropped_frames_ttl++;
		rcu_read_unlock();
		return;
	}
	ttl--;

	if (ifmsh->mshcfg.dot11MeshForwarding) {
		mesh_path_sel_frame_tx(MPATH_RANN, flags, orig_addr,
				       cpu_to_le32(orig_sn),
				       0, NULL, 0, broadcast_addr,
				       hopcount, ttl, cpu_to_le32(interval),
				       cpu_to_le32(metric + metric_txsta),
				       0, sdata);
	}

	rcu_read_unlock();
}