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
struct uart_port {int /*<<< orphan*/  mapbase; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MAP_SIZE ; 
 scalar_t__ request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char* s3c24xx_serial_portname (struct uart_port*) ; 

__attribute__((used)) static int s3c24xx_serial_request_port(struct uart_port *port)
{
	const char *name = s3c24xx_serial_portname(port);
	return request_mem_region(port->mapbase, MAP_SIZE, name) ? 0 : -EBUSY;
}