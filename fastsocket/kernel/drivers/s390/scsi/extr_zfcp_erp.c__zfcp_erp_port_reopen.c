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
struct zfcp_port {int /*<<< orphan*/  adapter; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ZFCP_ERP_ACTION_REOPEN_PORT ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int zfcp_erp_action_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zfcp_port*,int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  zfcp_erp_port_block (struct zfcp_port*,int) ; 
 int /*<<< orphan*/  zfcp_erp_port_failed (struct zfcp_port*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_scsi_schedule_rport_block (struct zfcp_port*) ; 

__attribute__((used)) static int _zfcp_erp_port_reopen(struct zfcp_port *port, int clear, char *id,
				 void *ref)
{
	zfcp_erp_port_block(port, clear);
	zfcp_scsi_schedule_rport_block(port);

	if (atomic_read(&port->status) & ZFCP_STATUS_COMMON_ERP_FAILED) {
		/* ensure propagation of failed status to new devices */
		zfcp_erp_port_failed(port, "erpreo1", NULL);
		return -EIO;
	}

	return zfcp_erp_action_enqueue(ZFCP_ERP_ACTION_REOPEN_PORT,
				       port->adapter, port, NULL, id, ref);
}