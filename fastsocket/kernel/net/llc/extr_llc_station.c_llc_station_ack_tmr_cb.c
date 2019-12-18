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
struct sk_buff {int dummy; } ;
struct llc_station_state_ev {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LLC_STATION_EV_TYPE_ACK_TMR ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct llc_station_state_ev* llc_station_ev (struct sk_buff*) ; 
 int /*<<< orphan*/  llc_station_state_process (struct sk_buff*) ; 

__attribute__((used)) static void llc_station_ack_tmr_cb(unsigned long timeout_data)
{
	struct sk_buff *skb = alloc_skb(0, GFP_ATOMIC);

	if (skb) {
		struct llc_station_state_ev *ev = llc_station_ev(skb);

		ev->type = LLC_STATION_EV_TYPE_ACK_TMR;
		llc_station_state_process(skb);
	}
}