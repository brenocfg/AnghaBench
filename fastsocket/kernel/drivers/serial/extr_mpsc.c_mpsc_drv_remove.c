#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct platform_device {size_t id; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t MPSC_NUM_CTLRS ; 
 int /*<<< orphan*/  mpsc_drv_unmap_regs (TYPE_1__*) ; 
 TYPE_1__* mpsc_ports ; 
 int /*<<< orphan*/  mpsc_reg ; 
 int /*<<< orphan*/  mpsc_release_port (struct uart_port*) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpsc_drv_remove(struct platform_device *dev)
{
	pr_debug("mpsc_drv_exit: Removing MPSC %d\n", dev->id);

	if (dev->id < MPSC_NUM_CTLRS) {
		uart_remove_one_port(&mpsc_reg, &mpsc_ports[dev->id].port);
		mpsc_release_port((struct uart_port *)
				&mpsc_ports[dev->id].port);
		mpsc_drv_unmap_regs(&mpsc_ports[dev->id]);
		return 0;
	} else {
		return -ENODEV;
	}
}