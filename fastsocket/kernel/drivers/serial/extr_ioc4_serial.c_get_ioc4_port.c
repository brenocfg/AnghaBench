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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct ioc4_port {struct uart_port* ip_port; struct uart_port** ip_all_ports; } ;
struct ioc4_driver_data {struct ioc4_control* idd_serial_data; } ;
struct ioc4_control {TYPE_1__* ic_port; } ;
struct TYPE_2__ {struct ioc4_port* icp_port; } ;

/* Variables and functions */
 int IOC4_NUM_SERIAL_PORTS ; 
 int UART_PORT_COUNT ; 
 int UART_PORT_MIN ; 
 struct ioc4_driver_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ioc4_port *get_ioc4_port(struct uart_port *the_port, int set)
{
	struct ioc4_driver_data *idd = dev_get_drvdata(the_port->dev);
	struct ioc4_control *control = idd->idd_serial_data;
	struct ioc4_port *port;
	int port_num, port_type;

	if (control) {
		for ( port_num = 0; port_num < IOC4_NUM_SERIAL_PORTS;
							port_num++ ) {
			port = control->ic_port[port_num].icp_port;
			if (!port)
				continue;
			for (port_type = UART_PORT_MIN;
						port_type < UART_PORT_COUNT;
						port_type++) {
				if (the_port == port->ip_all_ports
							[port_type]) {
					/* set local copy */
					if (set) {
						port->ip_port = the_port;
					}
					return port;
				}
			}
		}
	}
	return NULL;
}