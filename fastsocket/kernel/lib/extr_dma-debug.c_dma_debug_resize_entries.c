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
typedef  scalar_t__ u32 ;
struct dma_debug_entry {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct dma_debug_entry* __dma_entry_alloc () ; 
 int /*<<< orphan*/  free_entries ; 
 int /*<<< orphan*/  free_entries_lock ; 
 int /*<<< orphan*/  kfree (struct dma_debug_entry*) ; 
 struct dma_debug_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nr_total_entries ; 
 int num_free_entries ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmp ; 

int dma_debug_resize_entries(u32 num_entries)
{
	int i, delta, ret = 0;
	unsigned long flags;
	struct dma_debug_entry *entry;
	LIST_HEAD(tmp);

	spin_lock_irqsave(&free_entries_lock, flags);

	if (nr_total_entries < num_entries) {
		delta = num_entries - nr_total_entries;

		spin_unlock_irqrestore(&free_entries_lock, flags);

		for (i = 0; i < delta; i++) {
			entry = kzalloc(sizeof(*entry), GFP_KERNEL);
			if (!entry)
				break;

			list_add_tail(&entry->list, &tmp);
		}

		spin_lock_irqsave(&free_entries_lock, flags);

		list_splice(&tmp, &free_entries);
		nr_total_entries += i;
		num_free_entries += i;
	} else {
		delta = nr_total_entries - num_entries;

		for (i = 0; i < delta && !list_empty(&free_entries); i++) {
			entry = __dma_entry_alloc();
			kfree(entry);
		}

		nr_total_entries -= i;
	}

	if (nr_total_entries != num_entries)
		ret = 1;

	spin_unlock_irqrestore(&free_entries_lock, flags);

	return ret;
}