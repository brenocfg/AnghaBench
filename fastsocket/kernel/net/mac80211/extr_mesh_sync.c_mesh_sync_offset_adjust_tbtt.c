#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_if_mesh {scalar_t__ mesh_sp_id; scalar_t__ sync_offset_clockdrift_max; int adjusting_tbtt; int /*<<< orphan*/  sync_offset_lock; int /*<<< orphan*/  wrkq_flags; } ;
struct TYPE_2__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IEEE80211_SYNC_METHOD_NEIGHBOR_OFFSET ; 
 int /*<<< orphan*/  MESH_WORK_DRIFT_ADJUST ; 
 scalar_t__ TOFFSET_MINIMUM_ADJUSTMENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  msync_dbg (struct ieee80211_sub_if_data*,char*,long long) ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mesh_sync_offset_adjust_tbtt(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;

	WARN_ON(ifmsh->mesh_sp_id != IEEE80211_SYNC_METHOD_NEIGHBOR_OFFSET);
	BUG_ON(!rcu_read_lock_held());

	spin_lock_bh(&ifmsh->sync_offset_lock);

	if (ifmsh->sync_offset_clockdrift_max > TOFFSET_MINIMUM_ADJUSTMENT) {
		/* Since ajusting the tsf here would
		 * require a possibly blocking call
		 * to the driver tsf setter, we punt
		 * the tsf adjustment to the mesh tasklet
		 */
		msync_dbg(sdata,
			  "TBTT : kicking off TBTT adjustment with clockdrift_max=%lld\n",
			  ifmsh->sync_offset_clockdrift_max);
		set_bit(MESH_WORK_DRIFT_ADJUST, &ifmsh->wrkq_flags);

		ifmsh->adjusting_tbtt = true;
	} else {
		msync_dbg(sdata,
			  "TBTT : max clockdrift=%lld; too small to adjust\n",
			  (long long)ifmsh->sync_offset_clockdrift_max);
		ifmsh->sync_offset_clockdrift_max = 0;

		ifmsh->adjusting_tbtt = false;
	}
	spin_unlock_bh(&ifmsh->sync_offset_lock);
}