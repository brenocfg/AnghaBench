#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct sge_rspq {int /*<<< orphan*/  rx_queue; } ;
struct sge_qset {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct sge_qset* rspq_to_qset (struct sge_rspq*) ; 
 int skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void offload_enqueue(struct sge_rspq *q, struct sk_buff *skb)
{
	int was_empty = skb_queue_empty(&q->rx_queue);

	__skb_queue_tail(&q->rx_queue, skb);

	if (was_empty) {
		struct sge_qset *qs = rspq_to_qset(q);

		napi_schedule(&qs->napi);
	}
}