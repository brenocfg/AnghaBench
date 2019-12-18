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
struct zfcp_port {int dummy; } ;
struct zfcp_adapter {int /*<<< orphan*/  peer_d_id; int /*<<< orphan*/  peer_wwpn; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct zfcp_port*) ; 
 int /*<<< orphan*/  _zfcp_erp_port_reopen (struct zfcp_port*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct zfcp_port* zfcp_port_enqueue (struct zfcp_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_port_put (struct zfcp_port*) ; 

__attribute__((used)) static void zfcp_erp_enqueue_ptp_port(struct zfcp_adapter *adapter)
{
	struct zfcp_port *port;
	port = zfcp_port_enqueue(adapter, adapter->peer_wwpn, 0,
				 adapter->peer_d_id);
	if (IS_ERR(port)) /* error or port already attached */
		return;
	_zfcp_erp_port_reopen(port, 0, "ereptp1", NULL);
	zfcp_port_put(port);
}