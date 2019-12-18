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
struct TYPE_3__ {int /*<<< orphan*/  bswapped; } ;
struct TYPE_4__ {TYPE_1__ hfcsx; } ;
struct IsdnCardState {int /*<<< orphan*/  HW_Flags; TYPE_2__ hw; } ;
struct BCState {scalar_t__ mode; int /*<<< orphan*/  rqueue; scalar_t__ channel; struct IsdnCardState* cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_RCVBUFREADY ; 
 int /*<<< orphan*/  FLG_LOCK_ATOMIC ; 
 int /*<<< orphan*/  HFCSX_BTRANS_THRESHOLD ; 
 int /*<<< orphan*/  HFCSX_SEL_B1_RX ; 
 int /*<<< orphan*/  HFCSX_SEL_B2_RX ; 
 scalar_t__ L1_MODE_TRANS ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,scalar_t__) ; 
 struct sk_buff* read_fifo (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_event (struct BCState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
main_rec_hfcsx(struct BCState *bcs)
{
	struct IsdnCardState *cs = bcs->cs;
	int count = 5;
	struct sk_buff *skb;

      Begin:
	count--;
	if (test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
		debugl1(cs, "rec_data %d blocked", bcs->channel);
		return;
	}
	skb = read_fifo(cs, ((bcs->channel) && (!cs->hw.hfcsx.bswapped)) ? 
			HFCSX_SEL_B2_RX : HFCSX_SEL_B1_RX,
			(bcs->mode == L1_MODE_TRANS) ? 
			HFCSX_BTRANS_THRESHOLD : 0);

	if (skb) {
	  skb_queue_tail(&bcs->rqueue, skb);
	  schedule_event(bcs, B_RCVBUFREADY);
	}

	test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
	if (count && skb)
		goto Begin;
	return;
}