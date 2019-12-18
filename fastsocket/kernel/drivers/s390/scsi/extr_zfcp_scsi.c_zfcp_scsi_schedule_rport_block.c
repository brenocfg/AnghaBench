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
struct zfcp_port {int /*<<< orphan*/  rport_work; TYPE_1__* adapter; scalar_t__ rport; int /*<<< orphan*/  rport_task; } ;
struct TYPE_2__ {int /*<<< orphan*/  work_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPORT_DEL ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_port_get (struct zfcp_port*) ; 
 int /*<<< orphan*/  zfcp_port_put (struct zfcp_port*) ; 

void zfcp_scsi_schedule_rport_block(struct zfcp_port *port)
{
	zfcp_port_get(port);
	port->rport_task = RPORT_DEL;

	if (port->rport && queue_work(port->adapter->work_queue,
				      &port->rport_work))
		return;

	zfcp_port_put(port);
}