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
struct zfcp_port {struct fc_rport* rport; } ;
struct fc_rport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_remote_port_delete (struct fc_rport*) ; 

__attribute__((used)) static void zfcp_scsi_rport_block(struct zfcp_port *port)
{
	struct fc_rport *rport = port->rport;

	if (rport) {
		fc_remote_port_delete(rport);
		port->rport = NULL;
	}
}