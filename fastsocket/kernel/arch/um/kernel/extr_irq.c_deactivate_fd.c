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
struct irq_fd {int dummy; } ;

/* Variables and functions */
 struct irq_fd* find_irq_by_fd (int,int,int*) ; 
 int /*<<< orphan*/  ignore_sigio_fd (int) ; 
 int /*<<< orphan*/  irq_lock ; 
 int /*<<< orphan*/  os_set_pollfd (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void deactivate_fd(int fd, int irqnum)
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

	os_set_pollfd(i, -1);
	spin_unlock_irqrestore(&irq_lock, flags);

	ignore_sigio_fd(fd);
}