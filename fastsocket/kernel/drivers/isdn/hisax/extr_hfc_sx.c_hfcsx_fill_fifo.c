#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_7__ {int /*<<< orphan*/  bswapped; } ;
struct TYPE_8__ {TYPE_1__ hfcsx; } ;
struct IsdnCardState {TYPE_2__ hw; } ;
struct BCState {scalar_t__ mode; int /*<<< orphan*/  Flag; TYPE_5__* tx_skb; int /*<<< orphan*/  aclock; int /*<<< orphan*/  ackcnt; TYPE_4__* st; int /*<<< orphan*/  tx_cnt; scalar_t__ channel; struct IsdnCardState* cs; } ;
struct TYPE_11__ {scalar_t__ len; scalar_t__ pkt_type; } ;
struct TYPE_9__ {int /*<<< orphan*/  flag; } ;
struct TYPE_10__ {TYPE_3__ lli; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_BUSY ; 
 int /*<<< orphan*/  B_ACKPENDING ; 
 int /*<<< orphan*/  FLG_LLI_L1WAKEUP ; 
 int /*<<< orphan*/  HFCSX_BTRANS_THRESHOLD ; 
 int /*<<< orphan*/  HFCSX_SEL_B1_TX ; 
 int /*<<< orphan*/  HFCSX_SEL_B2_TX ; 
 scalar_t__ L1_MODE_TRANS ; 
 scalar_t__ PACKET_NOACK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_5__*) ; 
 int /*<<< orphan*/  schedule_event (struct BCState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ write_fifo (struct IsdnCardState*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hfcsx_fill_fifo(struct BCState *bcs)
{
	struct IsdnCardState *cs = bcs->cs;

	if (!bcs->tx_skb)
		return;
	if (bcs->tx_skb->len <= 0)
		return;

	if (write_fifo(cs, bcs->tx_skb, 
		       ((bcs->channel) && (!cs->hw.hfcsx.bswapped)) ? 
		       HFCSX_SEL_B2_TX : HFCSX_SEL_B1_TX,
		       (bcs->mode == L1_MODE_TRANS) ? 
		       HFCSX_BTRANS_THRESHOLD : 0)) {

	  bcs->tx_cnt -= bcs->tx_skb->len;
	  if (test_bit(FLG_LLI_L1WAKEUP,&bcs->st->lli.flag) &&
		(PACKET_NOACK != bcs->tx_skb->pkt_type)) {
		u_long	flags;
		spin_lock_irqsave(&bcs->aclock, flags);
		bcs->ackcnt += bcs->tx_skb->len;
		spin_unlock_irqrestore(&bcs->aclock, flags);
		schedule_event(bcs, B_ACKPENDING);
	  }
	  dev_kfree_skb_any(bcs->tx_skb);
	  bcs->tx_skb = NULL;
	  test_and_clear_bit(BC_FLG_BUSY, &bcs->Flag);
	}
}