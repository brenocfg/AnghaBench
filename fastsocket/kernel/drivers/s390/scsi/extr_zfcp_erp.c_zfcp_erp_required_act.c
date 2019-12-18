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
struct zfcp_unit {int /*<<< orphan*/  status; } ;
struct zfcp_port {int /*<<< orphan*/  status; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; } ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 129 
#define  ZFCP_ERP_ACTION_REOPEN_UNIT 128 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int ZFCP_STATUS_COMMON_ERP_INUSE ; 
 int ZFCP_STATUS_COMMON_OPEN ; 
 int ZFCP_STATUS_COMMON_RUNNING ; 
 int ZFCP_STATUS_COMMON_UNBLOCKED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zfcp_erp_required_act(int want, struct zfcp_adapter *adapter,
				 struct zfcp_port *port,
				 struct zfcp_unit *unit)
{
	int need = want;
	int u_status, p_status, a_status;

	switch (want) {
	case ZFCP_ERP_ACTION_REOPEN_UNIT:
		u_status = atomic_read(&unit->status);
		if (u_status & ZFCP_STATUS_COMMON_ERP_INUSE)
			return 0;
		p_status = atomic_read(&port->status);
		if (!(p_status & ZFCP_STATUS_COMMON_RUNNING) ||
		      p_status & ZFCP_STATUS_COMMON_ERP_FAILED)
			return 0;
		if (!(p_status & ZFCP_STATUS_COMMON_UNBLOCKED))
			need = ZFCP_ERP_ACTION_REOPEN_PORT;
		/* fall through */
	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		p_status = atomic_read(&port->status);
		if (!(p_status & ZFCP_STATUS_COMMON_OPEN))
			need = ZFCP_ERP_ACTION_REOPEN_PORT;
		/* fall through */
	case ZFCP_ERP_ACTION_REOPEN_PORT:
		p_status = atomic_read(&port->status);
		if (p_status & ZFCP_STATUS_COMMON_ERP_INUSE)
			return 0;
		a_status = atomic_read(&adapter->status);
		if (!(a_status & ZFCP_STATUS_COMMON_RUNNING) ||
		      a_status & ZFCP_STATUS_COMMON_ERP_FAILED)
			return 0;
		if (!(a_status & ZFCP_STATUS_COMMON_UNBLOCKED))
			need = ZFCP_ERP_ACTION_REOPEN_ADAPTER;
		/* fall through */
	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		a_status = atomic_read(&adapter->status);
		if (a_status & ZFCP_STATUS_COMMON_ERP_INUSE)
			return 0;
		if (!(a_status & ZFCP_STATUS_COMMON_RUNNING) &&
		    !(a_status & ZFCP_STATUS_COMMON_OPEN))
			return 0; /* shutdown requested for closed adapter */
	}

	return need;
}