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
struct TYPE_2__ {int /*<<< orphan*/  mapbase; } ;
struct sa1100_port {TYPE_1__ port; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  UART_PORT_SIZE ; 
 int /*<<< orphan*/ * request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sa1100_request_port(struct uart_port *port)
{
	struct sa1100_port *sport = (struct sa1100_port *)port;

	return request_mem_region(sport->port.mapbase, UART_PORT_SIZE,
			"sa11x0-uart") != NULL ? 0 : -EBUSY;
}