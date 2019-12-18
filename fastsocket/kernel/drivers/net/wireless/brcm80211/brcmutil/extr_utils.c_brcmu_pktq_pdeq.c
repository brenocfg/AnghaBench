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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct pktq {int /*<<< orphan*/  len; TYPE_1__* q; } ;
struct TYPE_2__ {struct sk_buff_head skblist; } ;

/* Variables and functions */
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 

struct sk_buff *brcmu_pktq_pdeq(struct pktq *pq, int prec)
{
	struct sk_buff_head *q;
	struct sk_buff *p;

	q = &pq->q[prec].skblist;
	p = skb_dequeue(q);
	if (p == NULL)
		return NULL;

	pq->len--;
	return p;
}