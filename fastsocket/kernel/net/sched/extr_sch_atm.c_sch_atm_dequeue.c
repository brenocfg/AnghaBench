#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  truesize; struct atm_qdisc_data* data; } ;
struct TYPE_10__ {struct atm_flow_data* next; } ;
struct atm_qdisc_data {TYPE_1__ link; } ;
struct atm_flow_data {scalar_t__ hdr_len; TYPE_3__* vcc; int /*<<< orphan*/  hdr; TYPE_4__* q; struct atm_flow_data* next; } ;
struct Qdisc {int dummy; } ;
struct TYPE_15__ {TYPE_3__* vcc; } ;
struct TYPE_14__ {int /*<<< orphan*/  sk_wmem_alloc; } ;
struct TYPE_13__ {TYPE_2__* ops; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* send ) (TYPE_3__*,struct sk_buff*) ;} ;
struct TYPE_11__ {struct sk_buff* (* peek ) (TYPE_4__*) ;} ;

/* Variables and functions */
 TYPE_9__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  atm_may_send (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,struct atm_flow_data*,...) ; 
 struct sk_buff* qdisc_dequeue_peeked (TYPE_4__*) ; 
 struct atm_qdisc_data* qdisc_priv (struct Qdisc*) ; 
 TYPE_5__* sk_atm (TYPE_3__*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 struct Qdisc* skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,scalar_t__) ; 
 struct sk_buff* stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sch_atm_dequeue(unsigned long data)
{
	struct Qdisc *sch = (struct Qdisc *)data;
	struct atm_qdisc_data *p = qdisc_priv(sch);
	struct atm_flow_data *flow;
	struct sk_buff *skb;

	pr_debug("sch_atm_dequeue(sch %p,[qdisc %p])\n", sch, p);
	for (flow = p->link.next; flow; flow = flow->next)
		/*
		 * If traffic is properly shaped, this won't generate nasty
		 * little bursts. Otherwise, it may ... (but that's okay)
		 */
		while ((skb = flow->q->ops->peek(flow->q))) {
			if (!atm_may_send(flow->vcc, skb->truesize))
				break;

			skb = qdisc_dequeue_peeked(flow->q);
			if (unlikely(!skb))
				break;

			pr_debug("atm_tc_dequeue: sending on class %p\n", flow);
			/* remove any LL header somebody else has attached */
			skb_pull(skb, skb_network_offset(skb));
			if (skb_headroom(skb) < flow->hdr_len) {
				struct sk_buff *new;

				new = skb_realloc_headroom(skb, flow->hdr_len);
				dev_kfree_skb(skb);
				if (!new)
					continue;
				skb = new;
			}
			pr_debug("sch_atm_dequeue: ip %p, data %p\n",
				 skb_network_header(skb), skb->data);
			ATM_SKB(skb)->vcc = flow->vcc;
			memcpy(skb_push(skb, flow->hdr_len), flow->hdr,
			       flow->hdr_len);
			atomic_add(skb->truesize,
				   &sk_atm(flow->vcc)->sk_wmem_alloc);
			/* atm.atm_options are already set by atm_tc_enqueue */
			flow->vcc->send(flow->vcc, skb);
		}
}