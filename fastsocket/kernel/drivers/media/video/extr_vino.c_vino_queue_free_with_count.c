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
struct vino_framebuffer_queue {scalar_t__ magic; int /*<<< orphan*/  type; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  out; int /*<<< orphan*/  in; scalar_t__ length; } ;
struct vino_framebuffer_fifo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VINO_MEMORY_NONE ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vino_free_buffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vino_queue_free_with_count(struct vino_framebuffer_queue *q,
				       unsigned int length)
{
	unsigned int i;

	q->length = 0;
	memset(&q->in, 0, sizeof(struct vino_framebuffer_fifo));
	memset(&q->out, 0, sizeof(struct vino_framebuffer_fifo));
	for (i = 0; i < length; i++) {
		dprintk("vino_queue_free_with_count(): freeing buffer %d\n",
			i);
		vino_free_buffer(q->buffer[i]);
		kfree(q->buffer[i]);
	}

	q->type = VINO_MEMORY_NONE;
	q->magic = 0;
}