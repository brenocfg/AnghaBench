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
typedef  int u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int cip; scalar_t__ fifosize; } ;
struct TYPE_4__ {TYPE_1__ hfc; } ;
struct IsdnCardState {int (* BC_Read_Reg ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;int debug; TYPE_2__ hw; int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int /*<<< orphan*/ ,int,int) ;} ;
struct BCState {scalar_t__ mode; int /*<<< orphan*/  Flag; int /*<<< orphan*/  squeue; scalar_t__ tx_skb; int /*<<< orphan*/  rqueue; int /*<<< orphan*/  channel; struct IsdnCardState* cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_BUSY ; 
 int /*<<< orphan*/  B_RCVBUFREADY ; 
 int /*<<< orphan*/  B_XMTBUFREADY ; 
 int HFC_CHANNEL (int /*<<< orphan*/ ) ; 
 int HFC_CIP ; 
 int /*<<< orphan*/  HFC_DATA ; 
 int HFC_F1 ; 
 int HFC_F2 ; 
 int HFC_REC ; 
 int /*<<< orphan*/  HFC_STATUS ; 
 int HFC_Z1 ; 
 int HFC_Z2 ; 
 int L1_DEB_HSCX ; 
 scalar_t__ L1_MODE_HDLC ; 
 scalar_t__ L1_MODE_TRANS ; 
 int ReadZReg (struct BCState*,int) ; 
 int /*<<< orphan*/  WaitForBusy (struct IsdnCardState*) ; 
 int /*<<< orphan*/  WaitNoBusy (struct IsdnCardState*) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int /*<<< orphan*/ ,int,int,...) ; 
 struct sk_buff* hfc_empty_fifo (struct BCState*,int) ; 
 int /*<<< orphan*/  hfc_fill_fifo (struct BCState*) ; 
 int /*<<< orphan*/  schedule_event (struct BCState*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
main_irq_hfc(struct BCState *bcs)
{
	struct IsdnCardState *cs = bcs->cs;
	int z1, z2, rcnt;
	u_char f1, f2, cip;
	int receive, transmit, count = 5;
	struct sk_buff *skb;

      Begin:
	count--;
	cip = HFC_CIP | HFC_F1 | HFC_REC | HFC_CHANNEL(bcs->channel);
	if ((cip & 0xc3) != (cs->hw.hfc.cip & 0xc3)) {
		cs->BC_Write_Reg(cs, HFC_STATUS, cip, cip);
		WaitForBusy(cs);
	}
	WaitNoBusy(cs);
	receive = 0;
	if (bcs->mode == L1_MODE_HDLC) {
		f1 = cs->BC_Read_Reg(cs, HFC_DATA, cip);
		cip = HFC_CIP | HFC_F2 | HFC_REC | HFC_CHANNEL(bcs->channel);
		WaitNoBusy(cs);
		f2 = cs->BC_Read_Reg(cs, HFC_DATA, cip);
		if (f1 != f2) {
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "hfc rec %d f1(%d) f2(%d)",
					bcs->channel, f1, f2);
			receive = 1; 
		}
	}
	if (receive || (bcs->mode == L1_MODE_TRANS)) {
		WaitForBusy(cs);
		z1 = ReadZReg(bcs, HFC_Z1 | HFC_REC | HFC_CHANNEL(bcs->channel));
		z2 = ReadZReg(bcs, HFC_Z2 | HFC_REC | HFC_CHANNEL(bcs->channel));
		rcnt = z1 - z2;
		if (rcnt < 0)
			rcnt += cs->hw.hfc.fifosize;
		if ((bcs->mode == L1_MODE_HDLC) || (rcnt)) {
			rcnt++;
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "hfc rec %d z1(%x) z2(%x) cnt(%d)",
					bcs->channel, z1, z2, rcnt);
			/*              sti(); */
			if ((skb = hfc_empty_fifo(bcs, rcnt))) {
				skb_queue_tail(&bcs->rqueue, skb);
				schedule_event(bcs, B_RCVBUFREADY);
			}
		}
		receive = 1;
	}
	if (bcs->tx_skb) {
		transmit = 1;
		test_and_set_bit(BC_FLG_BUSY, &bcs->Flag);
		hfc_fill_fifo(bcs);
		if (test_bit(BC_FLG_BUSY, &bcs->Flag))
			transmit = 0;
	} else {
		if ((bcs->tx_skb = skb_dequeue(&bcs->squeue))) {
			transmit = 1;
			test_and_set_bit(BC_FLG_BUSY, &bcs->Flag);
			hfc_fill_fifo(bcs);
			if (test_bit(BC_FLG_BUSY, &bcs->Flag))
				transmit = 0;
		} else {
			transmit = 0;
			schedule_event(bcs, B_XMTBUFREADY);
		}
	}
	if ((receive || transmit) && count)
		goto Begin;
	return;
}