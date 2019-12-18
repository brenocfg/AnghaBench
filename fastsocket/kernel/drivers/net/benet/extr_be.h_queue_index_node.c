#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {void* va; } ;
struct be_queue_info {int entry_size; TYPE_1__ dma_mem; } ;

/* Variables and functions */

__attribute__((used)) static inline void *queue_index_node(struct be_queue_info *q, u16 index)
{
	return q->dma_mem.va + index * q->entry_size;
}