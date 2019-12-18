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
struct vino_framebuffer_fifo {unsigned int head; int tail; unsigned int length; unsigned int* data; } ;

/* Variables and functions */

__attribute__((used)) static inline int vino_fifo_has_id(struct vino_framebuffer_fifo *f,
				   unsigned int id)
{
	unsigned int i;

	for (i = f->head; i == (f->tail - 1); i = (i + 1) % f->length) {
		if (f->data[i] == id)
			return 1;
	}

	return 0;
}