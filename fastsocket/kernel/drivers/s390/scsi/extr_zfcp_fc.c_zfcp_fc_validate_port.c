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
struct zfcp_port {scalar_t__ supported_classes; int /*<<< orphan*/  unit_list_head; int /*<<< orphan*/  status; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int dummy; } ;

/* Variables and functions */
 int ZFCP_STATUS_COMMON_NOESC ; 
 int /*<<< orphan*/  atomic_clear_mask (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_port_shutdown (struct zfcp_port*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_port_dequeue (struct zfcp_port*) ; 
 int /*<<< orphan*/  zfcp_port_put (struct zfcp_port*) ; 

__attribute__((used)) static void zfcp_fc_validate_port(struct zfcp_port *port)
{
	struct zfcp_adapter *adapter = port->adapter;

	if (!(atomic_read(&port->status) & ZFCP_STATUS_COMMON_NOESC))
		return;

	atomic_clear_mask(ZFCP_STATUS_COMMON_NOESC, &port->status);

	if ((port->supported_classes != 0) ||
	    !list_empty(&port->unit_list_head)) {
		zfcp_port_put(port);
		return;
	}
	zfcp_erp_port_shutdown(port, 0, "fcpval1", NULL);
	zfcp_erp_wait(adapter);
	zfcp_port_put(port);
	zfcp_port_dequeue(port);
}