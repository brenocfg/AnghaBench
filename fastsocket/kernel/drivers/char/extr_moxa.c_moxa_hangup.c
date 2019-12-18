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
struct tty_struct {struct moxa_port* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_wait; scalar_t__ count; } ;
struct moxa_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  moxa_close_port (struct tty_struct*) ; 
 int /*<<< orphan*/  moxa_openlock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void moxa_hangup(struct tty_struct *tty)
{
	struct moxa_port *ch;

	mutex_lock(&moxa_openlock);
	ch = tty->driver_data;
	if (ch == NULL) {
		mutex_unlock(&moxa_openlock);
		return;
	}
	ch->port.count = 0;
	moxa_close_port(tty);
	mutex_unlock(&moxa_openlock);

	wake_up_interruptible(&ch->port.open_wait);
}