#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct aarp_entry {struct aarp_entry* next; int /*<<< orphan*/  hwaddr; scalar_t__ expires_at; int /*<<< orphan*/  packet_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* request ) (TYPE_1__*,struct sk_buff*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* ddp_dl ; 
 scalar_t__ jiffies ; 
 struct aarp_entry** resolved ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int sysctl_aarp_expiry_time ; 
 int /*<<< orphan*/  unresolved_count ; 

__attribute__((used)) static void __aarp_resolved(struct aarp_entry **list, struct aarp_entry *a,
			    int hash)
{
	struct sk_buff *skb;

	while (*list)
		if (*list == a) {
			unresolved_count--;
			*list = a->next;

			/* Move into the resolved list */
			a->next = resolved[hash];
			resolved[hash] = a;

			/* Kick frames off */
			while ((skb = skb_dequeue(&a->packet_queue)) != NULL) {
				a->expires_at = jiffies +
						sysctl_aarp_expiry_time * 10;
				ddp_dl->request(ddp_dl, skb, a->hwaddr);
			}
		} else
			list = &((*list)->next);
}