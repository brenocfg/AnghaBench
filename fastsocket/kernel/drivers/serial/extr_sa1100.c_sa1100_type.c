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
struct TYPE_2__ {scalar_t__ type; } ;
struct sa1100_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ PORT_SA1100 ; 

__attribute__((used)) static const char *sa1100_type(struct uart_port *port)
{
	struct sa1100_port *sport = (struct sa1100_port *)port;

	return sport->port.type == PORT_SA1100 ? "SA1100" : NULL;
}