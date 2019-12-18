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
struct TYPE_2__ {int /*<<< orphan*/  work; scalar_t__ memory_used; int /*<<< orphan*/ * free; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; int /*<<< orphan*/  lock; } ;
struct tty_struct {TYPE_1__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_to_ldisc ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void tty_buffer_init(struct tty_struct *tty)
{
	spin_lock_init(&tty->buf.lock);
	tty->buf.head = NULL;
	tty->buf.tail = NULL;
	tty->buf.free = NULL;
	tty->buf.memory_used = 0;
	INIT_DELAYED_WORK(&tty->buf.work, flush_to_ldisc);
}