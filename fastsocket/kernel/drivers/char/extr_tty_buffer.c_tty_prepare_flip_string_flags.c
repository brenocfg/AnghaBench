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
struct TYPE_2__ {int /*<<< orphan*/  lock; struct tty_buffer* tail; } ;
struct tty_struct {TYPE_1__ buf; } ;
struct tty_buffer {unsigned char* char_buf_ptr; int used; char* flag_buf_ptr; } ;

/* Variables and functions */
 int __tty_buffer_request_room (struct tty_struct*,size_t) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int tty_prepare_flip_string_flags(struct tty_struct *tty,
			unsigned char **chars, char **flags, size_t size)
{
	int space;
	unsigned long __flags;
	struct tty_buffer *tb;

	spin_lock_irqsave(&tty->buf.lock, __flags);
	space = __tty_buffer_request_room(tty, size);

	tb = tty->buf.tail;
	if (likely(space)) {
		*chars = tb->char_buf_ptr + tb->used;
		*flags = tb->flag_buf_ptr + tb->used;
		tb->used += space;
	}
	spin_unlock_irqrestore(&tty->buf.lock, __flags);
	return space;
}