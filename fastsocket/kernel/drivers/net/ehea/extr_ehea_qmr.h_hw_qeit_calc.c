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
typedef  size_t u64 ;
struct hw_queue {size_t queue_length; struct ehea_page** queue_pages; } ;
struct ehea_page {void* entries; } ;

/* Variables and functions */
 size_t EHEA_PAGESHIFT ; 
 int EHEA_PAGESIZE ; 

__attribute__((used)) static inline void *hw_qeit_calc(struct hw_queue *queue, u64 q_offset)
{
	struct ehea_page *current_page;

	if (q_offset >= queue->queue_length)
		q_offset -= queue->queue_length;
	current_page = (queue->queue_pages)[q_offset >> EHEA_PAGESHIFT];
	return &current_page->entries[q_offset & (EHEA_PAGESIZE - 1)];
}