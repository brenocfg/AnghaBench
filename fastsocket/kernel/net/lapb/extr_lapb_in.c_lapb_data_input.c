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
struct lapb_frame {int dummy; } ;
struct lapb_cb {int state; } ;

/* Variables and functions */
#define  LAPB_STATE_0 132 
#define  LAPB_STATE_1 131 
#define  LAPB_STATE_2 130 
#define  LAPB_STATE_3 129 
#define  LAPB_STATE_4 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ lapb_decode (struct lapb_cb*,struct sk_buff*,struct lapb_frame*) ; 
 int /*<<< orphan*/  lapb_kick (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_state0_machine (struct lapb_cb*,struct sk_buff*,struct lapb_frame*) ; 
 int /*<<< orphan*/  lapb_state1_machine (struct lapb_cb*,struct sk_buff*,struct lapb_frame*) ; 
 int /*<<< orphan*/  lapb_state2_machine (struct lapb_cb*,struct sk_buff*,struct lapb_frame*) ; 
 int /*<<< orphan*/  lapb_state3_machine (struct lapb_cb*,struct sk_buff*,struct lapb_frame*) ; 
 int /*<<< orphan*/  lapb_state4_machine (struct lapb_cb*,struct sk_buff*,struct lapb_frame*) ; 

void lapb_data_input(struct lapb_cb *lapb, struct sk_buff *skb)
{
	struct lapb_frame frame;

	if (lapb_decode(lapb, skb, &frame) < 0) {
		kfree_skb(skb);
		return;
	}

	switch (lapb->state) {
	case LAPB_STATE_0:
		lapb_state0_machine(lapb, skb, &frame); break;
	case LAPB_STATE_1:
		lapb_state1_machine(lapb, skb, &frame); break;
	case LAPB_STATE_2:
		lapb_state2_machine(lapb, skb, &frame); break;
	case LAPB_STATE_3:
		lapb_state3_machine(lapb, skb, &frame); break;
	case LAPB_STATE_4:
		lapb_state4_machine(lapb, skb, &frame); break;
	}

	lapb_kick(lapb);
}