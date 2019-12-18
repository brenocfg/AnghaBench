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
struct TYPE_6__ {scalar_t__ type; int* hw_queue; int cab_queue; } ;
struct ieee80211_sub_if_data {TYPE_3__ vif; TYPE_2__* local; } ;
struct TYPE_4__ {int queues; int flags; } ;
struct TYPE_5__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE80211_HW_QUEUE_CONTROL ; 
 int IEEE80211_INVAL_HW_QUEUE ; 
 int IEEE80211_NUM_ACS ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

__attribute__((used)) static int ieee80211_check_queues(struct ieee80211_sub_if_data *sdata)
{
	int n_queues = sdata->local->hw.queues;
	int i;

	if (sdata->vif.type != NL80211_IFTYPE_P2P_DEVICE) {
		for (i = 0; i < IEEE80211_NUM_ACS; i++) {
			if (WARN_ON_ONCE(sdata->vif.hw_queue[i] ==
					 IEEE80211_INVAL_HW_QUEUE))
				return -EINVAL;
			if (WARN_ON_ONCE(sdata->vif.hw_queue[i] >=
					 n_queues))
				return -EINVAL;
		}
	}

	if ((sdata->vif.type != NL80211_IFTYPE_AP &&
	     sdata->vif.type != NL80211_IFTYPE_MESH_POINT) ||
	    !(sdata->local->hw.flags & IEEE80211_HW_QUEUE_CONTROL)) {
		sdata->vif.cab_queue = IEEE80211_INVAL_HW_QUEUE;
		return 0;
	}

	if (WARN_ON_ONCE(sdata->vif.cab_queue == IEEE80211_INVAL_HW_QUEUE))
		return -EINVAL;

	if (WARN_ON_ONCE(sdata->vif.cab_queue >= n_queues))
		return -EINVAL;

	return 0;
}