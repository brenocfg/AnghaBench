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
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {TYPE_1__ ev_q; } ;

/* Variables and functions */
 TYPE_2__ llc_main_station ; 
 int /*<<< orphan*/  llc_station_next_state (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void llc_station_service_events(void)
{
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&llc_main_station.ev_q.list)) != NULL)
		llc_station_next_state(skb);
}