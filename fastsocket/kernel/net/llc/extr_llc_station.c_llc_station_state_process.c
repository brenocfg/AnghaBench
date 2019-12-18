#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {TYPE_1__ ev_q; } ;

/* Variables and functions */
 TYPE_2__ llc_main_station ; 
 int /*<<< orphan*/  llc_station_service_events () ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void llc_station_state_process(struct sk_buff *skb)
{
	spin_lock_bh(&llc_main_station.ev_q.lock);
	skb_queue_tail(&llc_main_station.ev_q.list, skb);
	llc_station_service_events();
	spin_unlock_bh(&llc_main_station.ev_q.lock);
}