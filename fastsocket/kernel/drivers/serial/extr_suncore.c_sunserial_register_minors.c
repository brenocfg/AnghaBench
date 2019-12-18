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
struct uart_driver {int minor; int nr; TYPE_1__* tty_driver; } ;
struct TYPE_2__ {int name_base; } ;

/* Variables and functions */
 int sunserial_current_minor ; 
 int uart_register_driver (struct uart_driver*) ; 

int sunserial_register_minors(struct uart_driver *drv, int count)
{
	int err = 0;

	drv->minor = sunserial_current_minor;
	drv->nr += count;
	/* Register the driver on the first call */
	if (drv->nr == count)
		err = uart_register_driver(drv);
	if (err == 0) {
		sunserial_current_minor += count;
		drv->tty_driver->name_base = drv->minor - 64;
	}
	return err;
}