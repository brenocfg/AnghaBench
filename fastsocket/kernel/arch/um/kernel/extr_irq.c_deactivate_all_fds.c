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
struct irq_fd {int /*<<< orphan*/  fd; struct irq_fd* next; } ;

/* Variables and functions */
 struct irq_fd* active_fds ; 
 int os_clear_fd_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_set_ioignore () ; 

int deactivate_all_fds(void)
{
	struct irq_fd *irq;
	int err;

	for (irq = active_fds; irq != NULL; irq = irq->next) {
		err = os_clear_fd_async(irq->fd);
		if (err)
			return err;
	}
	/* If there is a signal already queued, after unblocking ignore it */
	os_set_ioignore();

	return 0;
}