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
struct uvc_video_queue {unsigned int count; int /*<<< orphan*/  mem; TYPE_1__* buffer; } ;
struct TYPE_2__ {scalar_t__ vma_use_count; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __uvc_free_buffers(struct uvc_video_queue *queue)
{
	unsigned int i;

	for (i = 0; i < queue->count; ++i) {
		if (queue->buffer[i].vma_use_count != 0)
			return -EBUSY;
	}

	if (queue->count) {
		vfree(queue->mem);
		queue->count = 0;
	}

	return 0;
}