#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wlcore_hw_queue_iter_data {int cur_running; int /*<<< orphan*/  hw_queue_map; struct ieee80211_vif* vif; } ;
struct ieee80211_vif {int* hw_queue; } ;

/* Variables and functions */
 int IEEE80211_INVAL_HW_QUEUE ; 
 int NUM_TX_QUEUES ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlcore_hw_queue_iter(void *data, u8 *mac,
				 struct ieee80211_vif *vif)
{
	struct wlcore_hw_queue_iter_data *iter_data = data;

	if (WARN_ON_ONCE(vif->hw_queue[0] == IEEE80211_INVAL_HW_QUEUE))
		return;

	if (iter_data->cur_running || vif == iter_data->vif) {
		iter_data->cur_running = true;
		return;
	}

	__set_bit(vif->hw_queue[0] / NUM_TX_QUEUES, iter_data->hw_queue_map);
}