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
struct per_user_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int irq_from_evtchn (int) ; 
 int /*<<< orphan*/ ** port_user ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int,void*) ; 

__attribute__((used)) static void evtchn_unbind_from_user(struct per_user_data *u, int port)
{
	int irq = irq_from_evtchn(port);

	unbind_from_irqhandler(irq, (void *)(unsigned long)port);

	/* make sure we unbind the irq handler before clearing the port */
	barrier();

	port_user[port] = NULL;
}