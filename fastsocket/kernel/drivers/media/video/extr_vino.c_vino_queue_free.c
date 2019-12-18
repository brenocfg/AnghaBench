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
struct vino_framebuffer_queue {scalar_t__ magic; scalar_t__ type; int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ VINO_MEMORY_MMAP ; 
 scalar_t__ VINO_QUEUE_MAGIC ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vino_queue_free_with_count (struct vino_framebuffer_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vino_queue_free(struct vino_framebuffer_queue *q)
{
	dprintk("vino_queue_free():\n");

	if (q->magic != VINO_QUEUE_MAGIC)
		return;
	if (q->type != VINO_MEMORY_MMAP)
		return;

	mutex_lock(&q->queue_mutex);

	vino_queue_free_with_count(q, q->length);

	mutex_unlock(&q->queue_mutex);
}