#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nf_queue_entry {TYPE_1__* elem; TYPE_2__* skb; scalar_t__ outdev; scalar_t__ indev; } ;
struct nf_bridge_info {scalar_t__ physoutdev; scalar_t__ physindev; } ;
struct TYPE_4__ {struct nf_bridge_info* nf_bridge; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (scalar_t__) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_queue_entry_release_refs(struct nf_queue_entry *entry)
{
	/* Release those devices we held, or Alexey will kill me. */
	if (entry->indev)
		dev_put(entry->indev);
	if (entry->outdev)
		dev_put(entry->outdev);
#ifdef CONFIG_BRIDGE_NETFILTER
	if (entry->skb->nf_bridge) {
		struct nf_bridge_info *nf_bridge = entry->skb->nf_bridge;

		if (nf_bridge->physindev)
			dev_put(nf_bridge->physindev);
		if (nf_bridge->physoutdev)
			dev_put(nf_bridge->physoutdev);
	}
#endif
	/* Drop reference to owner of hook which queued us. */
	module_put(entry->elem->owner);
}