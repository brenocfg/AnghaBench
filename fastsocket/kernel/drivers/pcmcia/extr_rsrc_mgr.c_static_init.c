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
struct pcmcia_socket {int resource_setup_done; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int static_init(struct pcmcia_socket *s)
{
	unsigned long flags;

	/* the good thing about SS_CAP_STATIC_MAP sockets is
	 * that they don't need a resource database */

	spin_lock_irqsave(&s->lock, flags);
	s->resource_setup_done = 1;
	spin_unlock_irqrestore(&s->lock, flags);

	return 0;
}