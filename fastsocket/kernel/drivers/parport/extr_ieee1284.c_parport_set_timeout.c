#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pardevice {long timeout; TYPE_2__* port; } ;
struct TYPE_4__ {TYPE_1__* physport; } ;
struct TYPE_3__ {struct pardevice* cad; } ;

/* Variables and functions */
 int /*<<< orphan*/  parport_ieee1284_wakeup (TYPE_2__*) ; 

long parport_set_timeout (struct pardevice *dev, long inactivity)
{
	long int old = dev->timeout;

	dev->timeout = inactivity;

	if (dev->port->physport->cad == dev)
		parport_ieee1284_wakeup (dev->port);

	return old;
}