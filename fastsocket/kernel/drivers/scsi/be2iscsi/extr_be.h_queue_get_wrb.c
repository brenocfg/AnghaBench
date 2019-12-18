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
struct TYPE_2__ {void* va; } ;
struct be_queue_info {unsigned int entry_size; TYPE_1__ dma_mem; } ;

/* Variables and functions */

__attribute__((used)) static inline void *queue_get_wrb(struct be_queue_info *q, unsigned int wrb_num)
{
	return q->dma_mem.va + wrb_num * q->entry_size;
}