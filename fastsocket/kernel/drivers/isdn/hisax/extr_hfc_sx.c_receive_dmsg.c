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
struct IsdnCardState {int /*<<< orphan*/  HW_Flags; int /*<<< orphan*/  rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_RCVBUFREADY ; 
 int /*<<< orphan*/  FLG_LOCK_ATOMIC ; 
 int /*<<< orphan*/  HFCSX_SEL_D_RX ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 struct sk_buff* read_fifo (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_event (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int
receive_dmsg(struct IsdnCardState *cs)
{
	struct sk_buff *skb;
	int count = 5;

	if (test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
		debugl1(cs, "rec_dmsg blocked");
		return (1);
	}

	do {
	  skb = read_fifo(cs, HFCSX_SEL_D_RX, 0);
	  if (skb) {
	    skb_queue_tail(&cs->rq, skb);
	    schedule_event(cs, D_RCVBUFREADY);
	  }
	} while (--count && skb);

	test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
	return (1);
}