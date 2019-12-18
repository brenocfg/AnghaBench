#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int mode; struct BCState* bcs; int /*<<< orphan*/  hardware; int /*<<< orphan*/  bc; } ;
struct TYPE_13__ {int /*<<< orphan*/  l2l1; } ;
struct PStack {TYPE_7__ l1; TYPE_6__ l2; } ;
struct TYPE_8__ {int /*<<< orphan*/  rcvidx; int /*<<< orphan*/  rcvbuf; } ;
struct TYPE_9__ {TYPE_1__ hscx; } ;
struct BCState {int mode; struct PStack* st; TYPE_5__* cs; int /*<<< orphan*/  tx_cnt; TYPE_2__ hw; int /*<<< orphan*/  event; int /*<<< orphan*/  Flag; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/  squeue; int /*<<< orphan*/  rqueue; int /*<<< orphan*/  channel; } ;
struct TYPE_10__ {struct BCState* bcs; int /*<<< orphan*/  rcvbuf; } ;
struct TYPE_11__ {TYPE_3__ elsa; } ;
struct TYPE_12__ {TYPE_4__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_BUSY ; 
 int /*<<< orphan*/  BC_FLG_INIT ; 
#define  L1_MODE_HDLC 130 
#define  L1_MODE_MODEM 129 
#define  L1_MODE_TRANS 128 
 int /*<<< orphan*/  hscx_l2l1 ; 
 int /*<<< orphan*/  modem_l2l1 ; 
 int /*<<< orphan*/  open_hscxstate (int /*<<< orphan*/ ,struct BCState*) ; 
 int /*<<< orphan*/  setstack_l1_B (struct PStack*) ; 
 int /*<<< orphan*/  setstack_manager (struct PStack*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
setstack_elsa(struct PStack *st, struct BCState *bcs)
{

	bcs->channel = st->l1.bc;
	switch (st->l1.mode) {
		case L1_MODE_HDLC:
		case L1_MODE_TRANS:
			if (open_hscxstate(st->l1.hardware, bcs))
				return (-1);
			st->l2.l2l1 = hscx_l2l1;
			break;
		case L1_MODE_MODEM:
			bcs->mode = L1_MODE_MODEM;
			if (!test_and_set_bit(BC_FLG_INIT, &bcs->Flag)) {
				bcs->hw.hscx.rcvbuf = bcs->cs->hw.elsa.rcvbuf;
				skb_queue_head_init(&bcs->rqueue);
				skb_queue_head_init(&bcs->squeue);
			}
			bcs->tx_skb = NULL;
			test_and_clear_bit(BC_FLG_BUSY, &bcs->Flag);
			bcs->event = 0;
			bcs->hw.hscx.rcvidx = 0;
			bcs->tx_cnt = 0;
			bcs->cs->hw.elsa.bcs = bcs;
			st->l2.l2l1 = modem_l2l1;
			break;
	}
	st->l1.bcs = bcs;
	setstack_manager(st);
	bcs->st = st;
	setstack_l1_B(st);
	return (0);
}