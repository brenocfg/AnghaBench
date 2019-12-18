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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct sta_info {scalar_t__ plink_state; } ;
struct ieee802_11_elems {int preq_len; int prep_len; int perr_len; scalar_t__ rann; scalar_t__ perr; scalar_t__ prep; scalar_t__ preq; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct TYPE_5__ {scalar_t__ variable; } ;
struct TYPE_6__ {TYPE_1__ mesh_action; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ action; } ;
struct ieee80211_mgmt {TYPE_4__ u; int /*<<< orphan*/  sa; } ;

/* Variables and functions */
 int IEEE80211_MIN_ACTION_SIZE ; 
 int /*<<< orphan*/  MPATH_PREP ; 
 int /*<<< orphan*/  MPATH_PREQ ; 
 scalar_t__ NL80211_PLINK_ESTAB ; 
 int /*<<< orphan*/  hwmp_perr_frame_process (struct ieee80211_sub_if_data*,struct ieee80211_mgmt*,scalar_t__) ; 
 int /*<<< orphan*/  hwmp_prep_frame_process (struct ieee80211_sub_if_data*,struct ieee80211_mgmt*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hwmp_preq_frame_process (struct ieee80211_sub_if_data*,struct ieee80211_mgmt*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hwmp_rann_frame_process (struct ieee80211_sub_if_data*,struct ieee80211_mgmt*,scalar_t__) ; 
 scalar_t__ hwmp_route_info_get (struct ieee80211_sub_if_data*,struct ieee80211_mgmt*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802_11_parse_elems (scalar_t__,size_t,int,struct ieee802_11_elems*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 

void mesh_rx_path_sel_frame(struct ieee80211_sub_if_data *sdata,
			    struct ieee80211_mgmt *mgmt, size_t len)
{
	struct ieee802_11_elems elems;
	size_t baselen;
	u32 last_hop_metric;
	struct sta_info *sta;

	/* need action_code */
	if (len < IEEE80211_MIN_ACTION_SIZE + 1)
		return;

	rcu_read_lock();
	sta = sta_info_get(sdata, mgmt->sa);
	if (!sta || sta->plink_state != NL80211_PLINK_ESTAB) {
		rcu_read_unlock();
		return;
	}
	rcu_read_unlock();

	baselen = (u8 *) mgmt->u.action.u.mesh_action.variable - (u8 *) mgmt;
	ieee802_11_parse_elems(mgmt->u.action.u.mesh_action.variable,
			       len - baselen, false, &elems);

	if (elems.preq) {
		if (elems.preq_len != 37)
			/* Right now we support just 1 destination and no AE */
			return;
		last_hop_metric = hwmp_route_info_get(sdata, mgmt, elems.preq,
						      MPATH_PREQ);
		if (last_hop_metric)
			hwmp_preq_frame_process(sdata, mgmt, elems.preq,
						last_hop_metric);
	}
	if (elems.prep) {
		if (elems.prep_len != 31)
			/* Right now we support no AE */
			return;
		last_hop_metric = hwmp_route_info_get(sdata, mgmt, elems.prep,
						      MPATH_PREP);
		if (last_hop_metric)
			hwmp_prep_frame_process(sdata, mgmt, elems.prep,
						last_hop_metric);
	}
	if (elems.perr) {
		if (elems.perr_len != 15)
			/* Right now we support only one destination per PERR */
			return;
		hwmp_perr_frame_process(sdata, mgmt, elems.perr);
	}
	if (elems.rann)
		hwmp_rann_frame_process(sdata, mgmt, elems.rann);
}