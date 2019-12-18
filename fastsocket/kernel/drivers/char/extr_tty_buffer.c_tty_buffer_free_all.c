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
struct TYPE_2__ {scalar_t__ memory_used; int /*<<< orphan*/ * tail; struct tty_buffer* free; struct tty_buffer* head; } ;
struct tty_struct {TYPE_1__ buf; } ;
struct tty_buffer {struct tty_buffer* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tty_buffer*) ; 

void tty_buffer_free_all(struct tty_struct *tty)
{
	struct tty_buffer *thead;
	while ((thead = tty->buf.head) != NULL) {
		tty->buf.head = thead->next;
		kfree(thead);
	}
	while ((thead = tty->buf.free) != NULL) {
		tty->buf.free = thead->next;
		kfree(thead);
	}
	tty->buf.tail = NULL;
	tty->buf.memory_used = 0;
}