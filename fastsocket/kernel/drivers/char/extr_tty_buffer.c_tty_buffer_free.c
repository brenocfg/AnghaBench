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
struct TYPE_2__ {int memory_used; struct tty_buffer* free; } ;
struct tty_struct {TYPE_1__ buf; } ;
struct tty_buffer {int size; struct tty_buffer* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct tty_buffer*) ; 

__attribute__((used)) static void tty_buffer_free(struct tty_struct *tty, struct tty_buffer *b)
{
	/* Dumb strategy for now - should keep some stats */
	tty->buf.memory_used -= b->size;
	WARN_ON(tty->buf.memory_used < 0);

	if (b->size >= 512)
		kfree(b);
	else {
		b->next = tty->buf.free;
		tty->buf.free = b;
	}
}