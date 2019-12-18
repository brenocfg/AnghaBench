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
struct queue_entry {int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00queue_unmap_skb (struct queue_entry*) ; 

void rt2x00queue_free_skb(struct queue_entry *entry)
{
	if (!entry->skb)
		return;

	rt2x00queue_unmap_skb(entry);
	dev_kfree_skb_any(entry->skb);
	entry->skb = NULL;
}