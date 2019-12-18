#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_8__ {int int_m1; int int_s1; } ;
struct TYPE_9__ {TYPE_3__ hfcD; } ;
struct TYPE_6__ {int ph_state; } ;
struct TYPE_7__ {TYPE_1__ hfcd; } ;
struct IsdnCardState {int debug; int (* readisac ) (struct IsdnCardState*,int /*<<< orphan*/ ) ;TYPE_4__ hw; int /*<<< orphan*/  HW_Flags; scalar_t__ tx_cnt; int /*<<< orphan*/  sq; TYPE_5__* tx_skb; int /*<<< orphan*/  dbusytimer; int /*<<< orphan*/  channel; int /*<<< orphan*/  squeue; TYPE_2__ dc; } ;
struct BCState {int debug; int (* readisac ) (struct IsdnCardState*,int /*<<< orphan*/ ) ;TYPE_4__ hw; int /*<<< orphan*/  HW_Flags; scalar_t__ tx_cnt; int /*<<< orphan*/  sq; TYPE_5__* tx_skb; int /*<<< orphan*/  dbusytimer; int /*<<< orphan*/  channel; int /*<<< orphan*/  squeue; TYPE_2__ dc; } ;
struct TYPE_10__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_XMTBUFREADY ; 
 int /*<<< orphan*/  D_CLEARBUSY ; 
 int /*<<< orphan*/  D_L1STATECHANGE ; 
 int /*<<< orphan*/  D_XMTBUFREADY ; 
 int /*<<< orphan*/  FLG_DBUSY_TIMER ; 
 int /*<<< orphan*/  FLG_L1_DBUSY ; 
 int /*<<< orphan*/  FLG_LOCK_ATOMIC ; 
 int /*<<< orphan*/  HFCD_STATES ; 
 int L1_DEB_ISAC ; 
 struct IsdnCardState* Sel_BCS (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,...) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (TYPE_5__*) ; 
 int /*<<< orphan*/  hfc_fill_dfifo (struct IsdnCardState*) ; 
 int /*<<< orphan*/  hfc_fill_fifo (struct IsdnCardState*) ; 
 int /*<<< orphan*/  main_rec_2bds0 (struct IsdnCardState*) ; 
 int /*<<< orphan*/  receive_dmsg (struct IsdnCardState*) ; 
 int /*<<< orphan*/  schedule_event (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 void* skb_dequeue (int /*<<< orphan*/ *) ; 
 int stub1 (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
hfc2bds0_interrupt(struct IsdnCardState *cs, u_char val)
{
       	u_char exval;
       	struct BCState *bcs;
	int count=15;

	if (cs->debug & L1_DEB_ISAC)
		debugl1(cs, "HFCD irq %x %s", val,
			test_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags) ?
			"locked" : "unlocked");
	val &= cs->hw.hfcD.int_m1;
	if (val & 0x40) { /* TE state machine irq */
		exval = cs->readisac(cs, HFCD_STATES) & 0xf;
		if (cs->debug & L1_DEB_ISAC)
			debugl1(cs, "ph_state chg %d->%d", cs->dc.hfcd.ph_state,
				exval);
		cs->dc.hfcd.ph_state = exval;
		schedule_event(cs, D_L1STATECHANGE);
		val &= ~0x40;
	}
	while (val) {
		if (test_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
			cs->hw.hfcD.int_s1 |= val;
			return;
		}
		if (cs->hw.hfcD.int_s1 & 0x18) {
			exval = val;
			val =  cs->hw.hfcD.int_s1;
			cs->hw.hfcD.int_s1 = exval;
		}	
		if (val & 0x08) {
			if (!(bcs=Sel_BCS(cs, 0))) {
				if (cs->debug)
					debugl1(cs, "hfcd spurious 0x08 IRQ");
			} else 
				main_rec_2bds0(bcs);
		}
		if (val & 0x10) {
			if (!(bcs=Sel_BCS(cs, 1))) {
				if (cs->debug)
					debugl1(cs, "hfcd spurious 0x10 IRQ");
			} else 
				main_rec_2bds0(bcs);
		}
		if (val & 0x01) {
			if (!(bcs=Sel_BCS(cs, 0))) {
				if (cs->debug)
					debugl1(cs, "hfcd spurious 0x01 IRQ");
			} else {
				if (bcs->tx_skb) {
					if (!test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
						hfc_fill_fifo(bcs);
						test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
					} else
						debugl1(cs,"fill_data %d blocked", bcs->channel);
				} else {
					if ((bcs->tx_skb = skb_dequeue(&bcs->squeue))) {
						if (!test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
							hfc_fill_fifo(bcs);
							test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
						} else
							debugl1(cs,"fill_data %d blocked", bcs->channel);
					} else {
						schedule_event(bcs, B_XMTBUFREADY);
					}
				}
			}
		}
		if (val & 0x02) {
			if (!(bcs=Sel_BCS(cs, 1))) {
				if (cs->debug)
					debugl1(cs, "hfcd spurious 0x02 IRQ");
			} else {
				if (bcs->tx_skb) {
					if (!test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
						hfc_fill_fifo(bcs);
						test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
					} else
						debugl1(cs,"fill_data %d blocked", bcs->channel);
				} else {
					if ((bcs->tx_skb = skb_dequeue(&bcs->squeue))) {
						if (!test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
							hfc_fill_fifo(bcs);
							test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
						} else
							debugl1(cs,"fill_data %d blocked", bcs->channel);
					} else {
						schedule_event(bcs, B_XMTBUFREADY);
					}
				}
			}
		}
		if (val & 0x20) {	/* receive dframe */
			receive_dmsg(cs);
		}
		if (val & 0x04) {	/* dframe transmitted */
			if (test_and_clear_bit(FLG_DBUSY_TIMER, &cs->HW_Flags))
				del_timer(&cs->dbusytimer);
			if (test_and_clear_bit(FLG_L1_DBUSY, &cs->HW_Flags))
				schedule_event(cs, D_CLEARBUSY);
			if (cs->tx_skb) {
				if (cs->tx_skb->len) {
					if (!test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
						hfc_fill_dfifo(cs);
						test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
					} else {
						debugl1(cs, "hfc_fill_dfifo irq blocked");
					}
					goto afterXPR;
				} else {
					dev_kfree_skb_irq(cs->tx_skb);
					cs->tx_cnt = 0;
					cs->tx_skb = NULL;
				}
			}
			if ((cs->tx_skb = skb_dequeue(&cs->sq))) {
				cs->tx_cnt = 0;
				if (!test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
					hfc_fill_dfifo(cs);
					test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
				} else {
					debugl1(cs, "hfc_fill_dfifo irq blocked");
				}
			} else
				schedule_event(cs, D_XMTBUFREADY);
		}
      afterXPR:
		if (cs->hw.hfcD.int_s1 && count--) {
			val = cs->hw.hfcD.int_s1;
			cs->hw.hfcD.int_s1 = 0;
			if (cs->debug & L1_DEB_ISAC)
				debugl1(cs, "HFCD irq %x loop %d", val, 15-count);
		} else
			val = 0;
	}
}