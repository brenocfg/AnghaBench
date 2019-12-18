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
struct vino_framebuffer_fifo {unsigned int length; scalar_t__ tail; scalar_t__ head; scalar_t__ used; } ;

/* Variables and functions */
 unsigned int VINO_FRAMEBUFFER_COUNT_MAX ; 

__attribute__((used)) static inline void vino_fifo_init(struct vino_framebuffer_fifo *f,
			   unsigned int length)
{
	f->length = 0;
	f->used = 0;
	f->head = 0;
	f->tail = 0;

	if (length > VINO_FRAMEBUFFER_COUNT_MAX)
		length = VINO_FRAMEBUFFER_COUNT_MAX;

	f->length = length;
}