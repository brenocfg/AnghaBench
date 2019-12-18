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
struct TYPE_6__ {int /*<<< orphan*/  (* l2l1 ) (struct PStack*,int,struct sk_buff*) ;int /*<<< orphan*/  flag; } ;
struct TYPE_5__ {TYPE_1__* bcs; } ;
struct PStack {TYPE_3__ l2; TYPE_2__ l1; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_LAPB ; 
 int PH_DATA ; 
 int REQUEST ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
enqueue_super(struct PStack *st,
	      struct sk_buff *skb)
{
	if (test_bit(FLG_LAPB, &st->l2.flag))
		st->l1.bcs->tx_cnt += skb->len;
	st->l2.l2l1(st, PH_DATA | REQUEST, skb);
}