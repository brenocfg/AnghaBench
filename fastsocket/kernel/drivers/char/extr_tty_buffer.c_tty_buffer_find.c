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
struct TYPE_2__ {size_t memory_used; struct tty_buffer* free; } ;
struct tty_struct {TYPE_1__ buf; } ;
struct tty_buffer {size_t size; struct tty_buffer* next; scalar_t__ read; scalar_t__ commit; scalar_t__ used; } ;

/* Variables and functions */
 struct tty_buffer* tty_buffer_alloc (struct tty_struct*,size_t) ; 

__attribute__((used)) static struct tty_buffer *tty_buffer_find(struct tty_struct *tty, size_t size)
{
	struct tty_buffer **tbh = &tty->buf.free;
	while ((*tbh) != NULL) {
		struct tty_buffer *t = *tbh;
		if (t->size >= size) {
			*tbh = t->next;
			t->next = NULL;
			t->used = 0;
			t->commit = 0;
			t->read = 0;
			tty->buf.memory_used += t->size;
			return t;
		}
		tbh = &((*tbh)->next);
	}
	/* Round the buffer size out */
	size = (size + 0xFF) & ~0xFF;
	return tty_buffer_alloc(tty, size);
	/* Should possibly check if this fails for the largest buffer we
	   have queued and recycle that ? */
}