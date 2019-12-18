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
struct uart_port {int dummy; } ;
struct ioc4_soft {scalar_t__ is_ioc4_serial_addr; int /*<<< orphan*/  ic_irq; struct ioc4_soft* ic_soft; int /*<<< orphan*/  ip_dma_ringbuf; int /*<<< orphan*/  ip_cpu_ringbuf; int /*<<< orphan*/  ip_pdev; TYPE_1__* ic_port; } ;
struct ioc4_serial {int dummy; } ;
struct ioc4_port {scalar_t__ is_ioc4_serial_addr; int /*<<< orphan*/  ic_irq; struct ioc4_port* ic_soft; int /*<<< orphan*/  ip_dma_ringbuf; int /*<<< orphan*/  ip_cpu_ringbuf; int /*<<< orphan*/  ip_pdev; TYPE_1__* ic_port; } ;
struct ioc4_driver_data {struct ioc4_soft* idd_serial_data; } ;
struct ioc4_control {scalar_t__ is_ioc4_serial_addr; int /*<<< orphan*/  ic_irq; struct ioc4_control* ic_soft; int /*<<< orphan*/  ip_dma_ringbuf; int /*<<< orphan*/  ip_cpu_ringbuf; int /*<<< orphan*/  ip_pdev; TYPE_1__* ic_port; } ;
struct TYPE_2__ {struct ioc4_soft* icp_port; struct uart_port* icp_uart_port; } ;

/* Variables and functions */
 int IOC4_NUM_SERIAL_PORTS ; 
 int /*<<< orphan*/  TOTAL_RING_BUF_SIZE ; 
 int UART_PORT_COUNT ; 
 int UART_PORT_MIN ; 
#define  UART_PORT_RS232 129 
#define  UART_PORT_RS422 128 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ioc4_soft*) ; 
 int /*<<< orphan*/  ioc4_uart_rs232 ; 
 int /*<<< orphan*/  ioc4_uart_rs422 ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ioc4_soft*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (unsigned long,int) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int ioc4_serial_remove_one(struct ioc4_driver_data *idd)
{
	int port_num, port_type;
	struct ioc4_control *control;
	struct uart_port *the_port;
	struct ioc4_port *port;
	struct ioc4_soft *soft;

	/* If serial driver did not attach, don't try to detach */
	control = idd->idd_serial_data;
	if (!control)
		return 0;

	for (port_num = 0; port_num < IOC4_NUM_SERIAL_PORTS; port_num++) {
		for (port_type = UART_PORT_MIN;
					port_type < UART_PORT_COUNT;
					port_type++) {
			the_port = &control->ic_port[port_num].icp_uart_port
							[port_type];
			if (the_port) {
				switch (port_type) {
				case UART_PORT_RS422:
					uart_remove_one_port(&ioc4_uart_rs422,
							the_port);
					break;
				default:
				case UART_PORT_RS232:
					uart_remove_one_port(&ioc4_uart_rs232,
							the_port);
					break;
				}
			}
		}
		port = control->ic_port[port_num].icp_port;
		/* we allocate in pairs */
		if (!(port_num & 1) && port) {
			pci_free_consistent(port->ip_pdev,
					TOTAL_RING_BUF_SIZE,
					port->ip_cpu_ringbuf,
					port->ip_dma_ringbuf);
			kfree(port);
		}
	}
	soft = control->ic_soft;
	if (soft) {
		free_irq(control->ic_irq, soft);
		if (soft->is_ioc4_serial_addr) {
			iounmap(soft->is_ioc4_serial_addr);
			release_mem_region((unsigned long)
			     soft->is_ioc4_serial_addr,
				sizeof(struct ioc4_serial));
		}
		kfree(soft);
	}
	kfree(control);
	idd->idd_serial_data = NULL;

	return 0;
}