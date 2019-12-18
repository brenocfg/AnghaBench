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
struct irq_fd {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_sigio_fd (int) ; 
 struct irq_fd* find_irq_by_fd (int,int,int*) ; 
 int /*<<< orphan*/  irq_lock ; 
 int /*<<< orphan*/  os_set_pollfd (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void reactivate_fd(int fd, int irqnum)
{
	struct irq_fd *irq;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&irq_lock, flags);
	irq = find_irq_by_fd(fd, irqnum, &i);
	if (irq == NULL) {
		spin_unlock_irqrestore(&irq_lock, flags);
		return;
	}
	os_set_pollfd(i, irq->fd);
	spin_unlock_irqrestore(&irq_lock, flags);

	add_sigio_fd(fd);
}