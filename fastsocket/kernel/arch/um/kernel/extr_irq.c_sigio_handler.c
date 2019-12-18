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
struct uml_pt_regs {int dummy; } ;
struct irq_fd {scalar_t__ current_events; int /*<<< orphan*/  irq; struct irq_fd* next; } ;

/* Variables and functions */
 int EINTR ; 
 struct irq_fd* active_fds ; 
 int /*<<< orphan*/  do_IRQ (int /*<<< orphan*/ ,struct uml_pt_regs*) ; 
 int /*<<< orphan*/  free_irqs () ; 
 int os_waiting_for_events (struct irq_fd*) ; 
 scalar_t__ smp_sigio_handler () ; 

void sigio_handler(int sig, struct uml_pt_regs *regs)
{
	struct irq_fd *irq_fd;
	int n;

	if (smp_sigio_handler())
		return;

	while (1) {
		n = os_waiting_for_events(active_fds);
		if (n <= 0) {
			if (n == -EINTR)
				continue;
			else break;
		}

		for (irq_fd = active_fds; irq_fd != NULL;
		     irq_fd = irq_fd->next) {
			if (irq_fd->current_events != 0) {
				irq_fd->current_events = 0;
				do_IRQ(irq_fd->irq, regs);
			}
		}
	}

	free_irqs();
}