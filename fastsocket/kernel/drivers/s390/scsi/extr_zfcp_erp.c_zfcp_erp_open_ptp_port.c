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
struct zfcp_port {scalar_t__ wwpn; int /*<<< orphan*/  d_id; } ;
struct zfcp_erp_action {struct zfcp_port* port; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {scalar_t__ peer_wwpn; int /*<<< orphan*/  peer_d_id; } ;

/* Variables and functions */
 int ZFCP_ERP_FAILED ; 
 int /*<<< orphan*/  zfcp_erp_port_failed (struct zfcp_port*,char*,int /*<<< orphan*/ *) ; 
 int zfcp_erp_port_strategy_open_port (struct zfcp_erp_action*) ; 

__attribute__((used)) static int zfcp_erp_open_ptp_port(struct zfcp_erp_action *act)
{
	struct zfcp_adapter *adapter = act->adapter;
	struct zfcp_port *port = act->port;

	if (port->wwpn != adapter->peer_wwpn) {
		zfcp_erp_port_failed(port, "eroptp1", NULL);
		return ZFCP_ERP_FAILED;
	}
	port->d_id = adapter->peer_d_id;
	return zfcp_erp_port_strategy_open_port(act);
}