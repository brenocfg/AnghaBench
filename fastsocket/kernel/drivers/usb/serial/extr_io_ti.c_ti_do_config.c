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
struct edgeport_port {TYPE_2__* port; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_4__ {int number; TYPE_1__* serial; } ;
struct TYPE_3__ {int minor; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ UMPM_UART1_PORT ; 
 int send_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_do_config(struct edgeport_port *port, int feature, int on)
{
	int port_number = port->port->number - port->port->serial->minor;
	on = !!on;	/* 1 or 0 not bitmask */
	return send_cmd(port->port->serial->dev,
			feature, (__u8)(UMPM_UART1_PORT + port_number),
			on, NULL, 0);
}