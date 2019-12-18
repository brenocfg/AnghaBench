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
struct netpoll_info {int /*<<< orphan*/  arp_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  netpoll_arp_reply (struct sk_buff*,struct netpoll_info*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void service_arp_queue(struct netpoll_info *npi)
{
	if (npi) {
		struct sk_buff *skb;

		while ((skb = skb_dequeue(&npi->arp_tx)))
			netpoll_arp_reply(skb, npi);
	}
}