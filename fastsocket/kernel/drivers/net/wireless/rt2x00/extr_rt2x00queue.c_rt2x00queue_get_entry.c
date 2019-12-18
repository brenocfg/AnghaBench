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
struct queue_entry {int dummy; } ;
struct data_queue {size_t* index; int /*<<< orphan*/  index_lock; struct queue_entry* entries; int /*<<< orphan*/  rt2x00dev; } ;
typedef  enum queue_index { ____Placeholder_queue_index } queue_index ;

/* Variables and functions */
 int Q_INDEX_MAX ; 
 int /*<<< orphan*/  rt2x00_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

struct queue_entry *rt2x00queue_get_entry(struct data_queue *queue,
					  enum queue_index index)
{
	struct queue_entry *entry;
	unsigned long irqflags;

	if (unlikely(index >= Q_INDEX_MAX)) {
		rt2x00_err(queue->rt2x00dev, "Entry requested from invalid index type (%d)\n",
			   index);
		return NULL;
	}

	spin_lock_irqsave(&queue->index_lock, irqflags);

	entry = &queue->entries[queue->index[index]];

	spin_unlock_irqrestore(&queue->index_lock, irqflags);

	return entry;
}