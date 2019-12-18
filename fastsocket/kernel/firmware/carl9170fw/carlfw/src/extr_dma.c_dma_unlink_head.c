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
struct dma_queue {struct dma_desc* head; } ;
struct dma_desc {struct dma_desc* lastAddr; struct dma_desc* nextAddr; } ;

/* Variables and functions */
 scalar_t__ queue_empty (struct dma_queue*) ; 

struct dma_desc *dma_unlink_head(struct dma_queue *queue)
{
	struct dma_desc *desc;

	if (queue_empty(queue))
		return NULL;

	desc = queue->head;

	queue->head = desc->lastAddr->nextAddr;

	/* poison nextAddr address */
	desc->lastAddr->nextAddr = desc->lastAddr;
	desc->lastAddr->lastAddr = desc->lastAddr;

	return desc;
}