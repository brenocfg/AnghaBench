#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nf_queue_entry {TYPE_5__* skb; TYPE_1__* outdev; TYPE_6__* indev; } ;
struct TYPE_12__ {unsigned long ifindex; } ;
struct TYPE_11__ {TYPE_4__* nf_bridge; } ;
struct TYPE_10__ {TYPE_3__* physoutdev; TYPE_2__* physindev; } ;
struct TYPE_9__ {unsigned long ifindex; } ;
struct TYPE_8__ {unsigned long ifindex; } ;
struct TYPE_7__ {unsigned long ifindex; } ;

/* Variables and functions */

__attribute__((used)) static int
dev_cmp(struct nf_queue_entry *entry, unsigned long ifindex)
{
	if (entry->indev)
		if (entry->indev->ifindex == ifindex)
			return 1;

	if (entry->outdev)
		if (entry->outdev->ifindex == ifindex)
			return 1;
#ifdef CONFIG_BRIDGE_NETFILTER
	if (entry->skb->nf_bridge) {
		if (entry->skb->nf_bridge->physindev &&
		    entry->skb->nf_bridge->physindev->ifindex == ifindex)
			return 1;
		if (entry->skb->nf_bridge->physoutdev &&
		    entry->skb->nf_bridge->physoutdev->ifindex == ifindex)
			return 1;
	}
#endif
	return 0;
}