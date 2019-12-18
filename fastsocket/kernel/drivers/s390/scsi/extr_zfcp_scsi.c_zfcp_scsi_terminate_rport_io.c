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
struct zfcp_port {int dummy; } ;
struct zfcp_adapter {int dummy; } ;
struct fc_rport {int /*<<< orphan*/  port_name; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  config_lock; } ;

/* Variables and functions */
 struct Scsi_Host* rport_to_shost (struct fc_rport*) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 TYPE_1__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_erp_port_forced_reopen (struct zfcp_port*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct zfcp_port* zfcp_get_port_by_wwpn (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_port_get (struct zfcp_port*) ; 
 int /*<<< orphan*/  zfcp_port_put (struct zfcp_port*) ; 

__attribute__((used)) static void zfcp_scsi_terminate_rport_io(struct fc_rport *rport)
{
	struct zfcp_port *port;
	struct Scsi_Host *shost = rport_to_shost(rport);
	struct zfcp_adapter *adapter =
		(struct zfcp_adapter *)shost->hostdata[0];

	write_lock_irq(&zfcp_data.config_lock);
	port = zfcp_get_port_by_wwpn(adapter, rport->port_name);
	if (port)
		zfcp_port_get(port);
	write_unlock_irq(&zfcp_data.config_lock);

	if (port) {
		zfcp_erp_port_forced_reopen(port, 0, "sctrpi1", NULL);
		zfcp_port_put(port);
	}
}