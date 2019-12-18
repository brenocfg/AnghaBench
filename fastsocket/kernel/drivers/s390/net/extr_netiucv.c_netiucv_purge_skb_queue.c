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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 

__attribute__((used)) static void netiucv_purge_skb_queue(struct sk_buff_head *q)
{
	struct sk_buff *skb;

	while ((skb = skb_dequeue(q))) {
		atomic_dec(&skb->users);
		dev_kfree_skb_any(skb);
	}
}