#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_queue; int /*<<< orphan*/  flag; } ;
struct TYPE_5__ {TYPE_1__* bcs; } ;
struct PStack {TYPE_3__ l2; TYPE_2__ l1; } ;
struct FsmInst {struct PStack* userdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_L3_INIT ; 
 int /*<<< orphan*/  FLG_LAPB ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ l2headersize (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_feed_i_if_reest(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;

	if (test_bit(FLG_LAPB, &st->l2.flag))
		st->l1.bcs->tx_cnt += skb->len + l2headersize(&st->l2, 0);
	if (!test_bit(FLG_L3_INIT, &st->l2.flag))
		skb_queue_tail(&st->l2.i_queue, skb);
	else
		dev_kfree_skb(skb);
}