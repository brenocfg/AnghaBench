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
 int /*<<< orphan*/ * request_mem_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial21285_name ; 

__attribute__((used)) static int serial21285_request_port(struct uart_port *port)
{
	return request_mem_region(port->mapbase, 32, serial21285_name)
			 != NULL ? 0 : -EBUSY;
}