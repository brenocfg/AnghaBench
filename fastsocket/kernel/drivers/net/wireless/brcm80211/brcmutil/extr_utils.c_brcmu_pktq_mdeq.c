#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct pktq {scalar_t__ len; int hi_prec; TYPE_1__* q; } ;
struct TYPE_2__ {struct sk_buff_head skblist; } ;

/* Variables and functions */
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 
 scalar_t__ skb_queue_empty (struct sk_buff_head*) ; 

struct sk_buff *brcmu_pktq_mdeq(struct pktq *pq, uint prec_bmp,
				      int *prec_out)
{
	struct sk_buff_head *q;
	struct sk_buff *p;
	int prec;

	if (pq->len == 0)
		return NULL;

	while ((prec = pq->hi_prec) > 0 &&
	       skb_queue_empty(&pq->q[prec].skblist))
		pq->hi_prec--;

	while ((prec_bmp & (1 << prec)) == 0 ||
	       skb_queue_empty(&pq->q[prec].skblist))
		if (prec-- == 0)
			return NULL;

	q = &pq->q[prec].skblist;
	p = skb_dequeue(q);
	if (p == NULL)
		return NULL;

	pq->len--;

	if (prec_out)
		*prec_out = prec;

	return p;
}