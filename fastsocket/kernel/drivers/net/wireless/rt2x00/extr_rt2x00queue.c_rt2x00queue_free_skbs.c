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
struct data_queue {unsigned int limit; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2x00queue_free_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2x00queue_free_skbs(struct data_queue *queue)
{
	unsigned int i;

	if (!queue->entries)
		return;

	for (i = 0; i < queue->limit; i++) {
		rt2x00queue_free_skb(&queue->entries[i]);
	}
}