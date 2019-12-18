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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {scalar_t__ cmd; int /*<<< orphan*/  dpath; scalar_t__ txcnt; } ;
struct TYPE_10__ {TYPE_3__ isar; } ;
struct BCState {scalar_t__ mode; int /*<<< orphan*/  Flag; TYPE_4__ hw; int /*<<< orphan*/  cs; int /*<<< orphan*/  squeue; TYPE_5__* tx_skb; int /*<<< orphan*/  aclock; int /*<<< orphan*/  ackcnt; TYPE_2__* st; } ;
struct TYPE_11__ {scalar_t__ pkt_type; scalar_t__ len; } ;
struct TYPE_7__ {int /*<<< orphan*/  flag; } ;
struct TYPE_8__ {TYPE_1__ lli; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_BUSY ; 
 int /*<<< orphan*/  BC_FLG_DLEETX ; 
 int /*<<< orphan*/  BC_FLG_LASTDATA ; 
 int /*<<< orphan*/  BC_FLG_LL_OK ; 
 int /*<<< orphan*/  BC_FLG_NMD_DATA ; 
 int /*<<< orphan*/  B_ACKPENDING ; 
 int /*<<< orphan*/  B_LL_CONNECT ; 
 int /*<<< orphan*/  B_XMTBUFREADY ; 
 int /*<<< orphan*/  FLG_LLI_L1WAKEUP ; 
 int ISAR_HIS_SDATA ; 
 scalar_t__ L1_MODE_FAX ; 
 scalar_t__ PACKET_NOACK ; 
 scalar_t__ PCTRL_CMD_FTH ; 
 scalar_t__ PCTRL_CMD_FTM ; 
 int SET_DPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_5__*) ; 
 int /*<<< orphan*/  isar_fill_fifo (struct BCState*) ; 
 int /*<<< orphan*/  schedule_event (struct BCState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendmsg (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 TYPE_5__* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
send_frames(struct BCState *bcs)
{
	if (bcs->tx_skb) {
		if (bcs->tx_skb->len) {
			isar_fill_fifo(bcs);
			return;
		} else {
			if (test_bit(FLG_LLI_L1WAKEUP,&bcs->st->lli.flag) &&
				(PACKET_NOACK != bcs->tx_skb->pkt_type)) {
				u_long	flags;
				spin_lock_irqsave(&bcs->aclock, flags);
				bcs->ackcnt += bcs->hw.isar.txcnt;
				spin_unlock_irqrestore(&bcs->aclock, flags);
				schedule_event(bcs, B_ACKPENDING);
			}
			if (bcs->mode == L1_MODE_FAX) {
				if (bcs->hw.isar.cmd == PCTRL_CMD_FTH) {
					if (test_bit(BC_FLG_LASTDATA, &bcs->Flag)) {
						test_and_set_bit(BC_FLG_NMD_DATA, &bcs->Flag);
					}
				} else if (bcs->hw.isar.cmd == PCTRL_CMD_FTM) {
					if (test_bit(BC_FLG_DLEETX, &bcs->Flag)) {
						test_and_set_bit(BC_FLG_LASTDATA, &bcs->Flag);
						test_and_set_bit(BC_FLG_NMD_DATA, &bcs->Flag);
					}
				}
			}
			dev_kfree_skb_any(bcs->tx_skb);
			bcs->hw.isar.txcnt = 0; 
			bcs->tx_skb = NULL;
		}
	}
	if ((bcs->tx_skb = skb_dequeue(&bcs->squeue))) {
		bcs->hw.isar.txcnt = 0;
		test_and_set_bit(BC_FLG_BUSY, &bcs->Flag);
		isar_fill_fifo(bcs);
	} else {
		if (test_and_clear_bit(BC_FLG_DLEETX, &bcs->Flag)) {
			if (test_and_clear_bit(BC_FLG_LASTDATA, &bcs->Flag)) {
				if (test_and_clear_bit(BC_FLG_NMD_DATA, &bcs->Flag)) {
					u_char dummy = 0;
					sendmsg(bcs->cs, SET_DPS(bcs->hw.isar.dpath) |
						ISAR_HIS_SDATA, 0x01, 1, &dummy);
				}
				test_and_set_bit(BC_FLG_LL_OK, &bcs->Flag);
			} else {
				schedule_event(bcs, B_LL_CONNECT);
			}
		}
		test_and_clear_bit(BC_FLG_BUSY, &bcs->Flag);
		schedule_event(bcs, B_XMTBUFREADY);
	}
}