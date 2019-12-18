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
struct zfcp_unit {int /*<<< orphan*/  fcp_lun; int /*<<< orphan*/  erp_counter; int /*<<< orphan*/  status; struct zfcp_port* port; } ;
struct zfcp_port {int /*<<< orphan*/  d_id; int /*<<< orphan*/  wwpn; TYPE_1__* adapter; } ;
struct zfcp_dbf {int dummy; } ;
struct TYPE_2__ {struct zfcp_dbf* dbf; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_dbf_rec_target (char*,void*,struct zfcp_dbf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zfcp_dbf_rec_unit(char *id, void *ref, struct zfcp_unit *unit)
{
	struct zfcp_port *port = unit->port;
	struct zfcp_dbf *dbf = port->adapter->dbf;

	zfcp_dbf_rec_target(id, ref, dbf, &unit->status,
				  &unit->erp_counter, port->wwpn, port->d_id,
				  unit->fcp_lun);
}