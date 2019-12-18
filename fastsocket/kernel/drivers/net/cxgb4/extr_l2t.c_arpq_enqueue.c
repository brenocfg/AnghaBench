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
struct sk_buff {struct sk_buff* next; } ;
struct l2t_entry {struct sk_buff* arpq_tail; struct sk_buff* arpq_head; } ;

/* Variables and functions */

__attribute__((used)) static inline void arpq_enqueue(struct l2t_entry *e, struct sk_buff *skb)
{
	skb->next = NULL;
	if (e->arpq_head)
		e->arpq_tail->next = skb;
	else
		e->arpq_head = skb;
	e->arpq_tail = skb;
}