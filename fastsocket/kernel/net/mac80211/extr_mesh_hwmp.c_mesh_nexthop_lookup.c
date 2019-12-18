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
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_4__ sta; } ;
struct sk_buff {scalar_t__ data; } ;
struct mesh_path {int flags; int /*<<< orphan*/  next_hop; scalar_t__ exp_time; } ;
struct TYPE_10__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  path_refresh_time; } ;
struct TYPE_7__ {TYPE_1__ mshcfg; } ;
struct TYPE_8__ {TYPE_2__ mesh; } ;
struct ieee80211_sub_if_data {TYPE_5__ vif; TYPE_3__ u; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr4; int /*<<< orphan*/ * addr3; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int MESH_PATH_ACTIVE ; 
 int MESH_PATH_FIXED ; 
 int MESH_PATH_RESOLVING ; 
 int PREQ_Q_F_REFRESH ; 
 int PREQ_Q_F_START ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_mps_set_frame_flags (struct ieee80211_sub_if_data*,struct sta_info*,struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mesh_path* mesh_path_lookup (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_queue_preq (struct mesh_path*,int) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct sta_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

int mesh_nexthop_lookup(struct ieee80211_sub_if_data *sdata,
			struct sk_buff *skb)
{
	struct mesh_path *mpath;
	struct sta_info *next_hop;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	u8 *target_addr = hdr->addr3;
	int err = -ENOENT;

	rcu_read_lock();
	mpath = mesh_path_lookup(sdata, target_addr);

	if (!mpath || !(mpath->flags & MESH_PATH_ACTIVE))
		goto endlookup;

	if (time_after(jiffies,
		       mpath->exp_time -
		       msecs_to_jiffies(sdata->u.mesh.mshcfg.path_refresh_time)) &&
	    ether_addr_equal(sdata->vif.addr, hdr->addr4) &&
	    !(mpath->flags & MESH_PATH_RESOLVING) &&
	    !(mpath->flags & MESH_PATH_FIXED))
		mesh_queue_preq(mpath, PREQ_Q_F_START | PREQ_Q_F_REFRESH);

	next_hop = rcu_dereference(mpath->next_hop);
	if (next_hop) {
		memcpy(hdr->addr1, next_hop->sta.addr, ETH_ALEN);
		memcpy(hdr->addr2, sdata->vif.addr, ETH_ALEN);
		ieee80211_mps_set_frame_flags(sdata, next_hop, hdr);
		err = 0;
	}

endlookup:
	rcu_read_unlock();
	return err;
}