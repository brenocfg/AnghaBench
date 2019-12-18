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
struct sk_buff_head {int dummy; } ;
struct sk_buff {size_t priority; } ;
struct pfifo_fast_priv {int bitmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; } ;
struct TYPE_4__ {scalar_t__ tx_queue_len; } ;

/* Variables and functions */
 size_t TC_PRIO_MAX ; 
 int __qdisc_enqueue_tail (struct sk_buff*,struct Qdisc*,struct sk_buff_head*) ; 
 struct sk_buff_head* band2list (struct pfifo_fast_priv*,int) ; 
 int* prio2band ; 
 TYPE_2__* qdisc_dev (struct Qdisc*) ; 
 int qdisc_drop (struct sk_buff*,struct Qdisc*) ; 
 struct pfifo_fast_priv* qdisc_priv (struct Qdisc*) ; 
 scalar_t__ skb_queue_len (TYPE_1__*) ; 

__attribute__((used)) static int pfifo_fast_enqueue(struct sk_buff *skb, struct Qdisc* qdisc)
{
	if (skb_queue_len(&qdisc->q) < qdisc_dev(qdisc)->tx_queue_len) {
		int band = prio2band[skb->priority & TC_PRIO_MAX];
		struct pfifo_fast_priv *priv = qdisc_priv(qdisc);
		struct sk_buff_head *list = band2list(priv, band);

		priv->bitmap |= (1 << band);
		qdisc->q.qlen++;
		return __qdisc_enqueue_tail(skb, qdisc, list);
	}

	return qdisc_drop(skb, qdisc);
}