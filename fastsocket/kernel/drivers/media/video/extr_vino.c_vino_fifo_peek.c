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
struct vino_framebuffer_fifo {scalar_t__ used; unsigned int* data; size_t head; } ;

/* Variables and functions */
 int VINO_QUEUE_ERROR ; 

__attribute__((used)) static int vino_fifo_peek(struct vino_framebuffer_fifo *f, unsigned int *id)
{
	if (f->used > 0) {
		*id = f->data[f->head];
	} else {
		return VINO_QUEUE_ERROR;
	}

	return 0;
}