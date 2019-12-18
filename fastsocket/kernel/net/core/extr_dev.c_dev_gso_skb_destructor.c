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
struct dev_gso_cb {int /*<<< orphan*/  (* destructor ) (struct sk_buff*) ;} ;

/* Variables and functions */
 struct dev_gso_cb* DEV_GSO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 

__attribute__((used)) static void dev_gso_skb_destructor(struct sk_buff *skb)
{
	struct dev_gso_cb *cb;

	do {
		struct sk_buff *nskb = skb->next;

		skb->next = nskb->next;
		nskb->next = NULL;
		kfree_skb(nskb);
	} while (skb->next);

	cb = DEV_GSO_CB(skb);
	if (cb->destructor)
		cb->destructor(skb);
}