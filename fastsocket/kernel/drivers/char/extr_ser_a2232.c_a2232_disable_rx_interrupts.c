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
struct a2232_port {int disable_rx; } ;

/* Variables and functions */

__attribute__((used)) static void a2232_disable_rx_interrupts(void *ptr)
{
	struct a2232_port *port;
	port = ptr;
	port->disable_rx = -1;
}