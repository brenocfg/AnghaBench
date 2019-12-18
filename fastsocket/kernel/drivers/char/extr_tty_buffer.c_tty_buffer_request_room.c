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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct tty_struct {TYPE_1__ buf; } ;

/* Variables and functions */
 int __tty_buffer_request_room (struct tty_struct*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int tty_buffer_request_room(struct tty_struct *tty, size_t size)
{
	unsigned long flags;
	int length;

	spin_lock_irqsave(&tty->buf.lock, flags);
	length = __tty_buffer_request_room(tty, size);
	spin_unlock_irqrestore(&tty->buf.lock, flags);
	return length;
}