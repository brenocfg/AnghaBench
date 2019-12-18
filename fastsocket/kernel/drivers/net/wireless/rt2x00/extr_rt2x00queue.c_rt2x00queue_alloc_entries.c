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
struct queue_entry {unsigned int entry_idx; int /*<<< orphan*/  priv_data; int /*<<< orphan*/ * skb; struct data_queue* queue; scalar_t__ flags; } ;
struct data_queue_desc {unsigned int entry_num; int priv_size; int /*<<< orphan*/  winfo_size; int /*<<< orphan*/  desc_size; int /*<<< orphan*/  data_size; } ;
struct data_queue {unsigned int limit; struct queue_entry* entries; int /*<<< orphan*/  winfo_size; int /*<<< orphan*/  desc_size; int /*<<< orphan*/  data_size; int /*<<< orphan*/  threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QUEUE_ENTRY_PRIV_OFFSET (struct queue_entry*,unsigned int,unsigned int,int,int) ; 
 struct queue_entry* kcalloc (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_reset (struct data_queue*) ; 

__attribute__((used)) static int rt2x00queue_alloc_entries(struct data_queue *queue,
				     const struct data_queue_desc *qdesc)
{
	struct queue_entry *entries;
	unsigned int entry_size;
	unsigned int i;

	rt2x00queue_reset(queue);

	queue->limit = qdesc->entry_num;
	queue->threshold = DIV_ROUND_UP(qdesc->entry_num, 10);
	queue->data_size = qdesc->data_size;
	queue->desc_size = qdesc->desc_size;
	queue->winfo_size = qdesc->winfo_size;

	/*
	 * Allocate all queue entries.
	 */
	entry_size = sizeof(*entries) + qdesc->priv_size;
	entries = kcalloc(queue->limit, entry_size, GFP_KERNEL);
	if (!entries)
		return -ENOMEM;

#define QUEUE_ENTRY_PRIV_OFFSET(__base, __index, __limit, __esize, __psize) \
	(((char *)(__base)) + ((__limit) * (__esize)) + \
	    ((__index) * (__psize)))

	for (i = 0; i < queue->limit; i++) {
		entries[i].flags = 0;
		entries[i].queue = queue;
		entries[i].skb = NULL;
		entries[i].entry_idx = i;
		entries[i].priv_data =
		    QUEUE_ENTRY_PRIV_OFFSET(entries, i, queue->limit,
					    sizeof(*entries), qdesc->priv_size);
	}

#undef QUEUE_ENTRY_PRIV_OFFSET

	queue->entries = entries;

	return 0;
}