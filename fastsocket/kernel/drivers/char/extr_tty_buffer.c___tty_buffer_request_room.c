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
struct TYPE_2__ {struct tty_buffer* tail; struct tty_buffer* head; } ;
struct tty_struct {TYPE_1__ buf; } ;
struct tty_buffer {int size; int used; int commit; struct tty_buffer* next; } ;

/* Variables and functions */
 struct tty_buffer* tty_buffer_find (struct tty_struct*,size_t) ; 

__attribute__((used)) static int __tty_buffer_request_room(struct tty_struct *tty, size_t size)
{
	struct tty_buffer *b, *n;
	int left;
	/* OPTIMISATION: We could keep a per tty "zero" sized buffer to
	   remove this conditional if its worth it. This would be invisible
	   to the callers */
	if ((b = tty->buf.tail) != NULL)
		left = b->size - b->used;
	else
		left = 0;

	if (left < size) {
		/* This is the slow path - looking for new buffers to use */
		if ((n = tty_buffer_find(tty, size)) != NULL) {
			if (b != NULL) {
				b->next = n;
				b->commit = b->used;
			} else
				tty->buf.head = n;
			tty->buf.tail = n;
		} else
			size = left;
	}

	return size;
}