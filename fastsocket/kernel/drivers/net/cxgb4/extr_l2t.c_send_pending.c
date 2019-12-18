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
struct l2t_entry {int /*<<< orphan*/ * arpq_tail; struct sk_buff* arpq_head; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  t4_ofld_send (struct adapter*,struct sk_buff*) ; 

__attribute__((used)) static void send_pending(struct adapter *adap, struct l2t_entry *e)
{
	while (e->arpq_head) {
		struct sk_buff *skb = e->arpq_head;

		e->arpq_head = skb->next;
		skb->next = NULL;
		t4_ofld_send(adap, skb);
	}
	e->arpq_tail = NULL;
}