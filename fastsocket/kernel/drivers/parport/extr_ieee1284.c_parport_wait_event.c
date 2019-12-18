#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {size_t data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct parport {size_t number; TYPE_3__* physport; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_6__ {TYPE_1__ ieee1284; TYPE_2__* cad; } ;
struct TYPE_5__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 size_t PARPORT_MAX ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 int /*<<< orphan*/  del_timer_sync (struct timer_list*) ; 
 int /*<<< orphan*/  destroy_timer_on_stack (struct timer_list*) ; 
 int down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer_on_stack (struct timer_list*) ; 
 scalar_t__ jiffies ; 
 struct parport** port_from_cookie ; 
 int /*<<< orphan*/  timeout_waiting_on_port ; 

int parport_wait_event (struct parport *port, signed long timeout)
{
	int ret;
	struct timer_list timer;

	if (!port->physport->cad->timeout)
		/* Zero timeout is special, and we can't down() the
		   semaphore. */
		return 1;

	init_timer_on_stack(&timer);
	timer.expires = jiffies + timeout;
	timer.function = timeout_waiting_on_port;
	port_from_cookie[port->number % PARPORT_MAX] = port;
	timer.data = port->number;

	add_timer (&timer);
	ret = down_interruptible (&port->physport->ieee1284.irq);
	if (!del_timer_sync(&timer) && !ret)
		/* Timed out. */
		ret = 1;

	destroy_timer_on_stack(&timer);

	return ret;
}