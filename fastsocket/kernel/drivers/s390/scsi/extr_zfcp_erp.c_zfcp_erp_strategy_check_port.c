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
struct zfcp_port {int /*<<< orphan*/  status; scalar_t__ wwpn; TYPE_2__* adapter; int /*<<< orphan*/  erp_counter; } ;
struct TYPE_4__ {TYPE_1__* ccw_device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ZFCP_ERP_EXIT ; 
#define  ZFCP_ERP_FAILED 129 
#define  ZFCP_ERP_SUCCEEDED 128 
 int ZFCP_MAX_ERPS ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int ZFCP_STATUS_COMMON_NOESC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 int /*<<< orphan*/  zfcp_erp_port_block (struct zfcp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_port_failed (struct zfcp_port*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_port_unblock (struct zfcp_port*) ; 

__attribute__((used)) static int zfcp_erp_strategy_check_port(struct zfcp_port *port, int result)
{
	switch (result) {
	case ZFCP_ERP_SUCCEEDED :
		atomic_set(&port->erp_counter, 0);
		zfcp_erp_port_unblock(port);
		break;

	case ZFCP_ERP_FAILED :
		if (atomic_read(&port->status) & ZFCP_STATUS_COMMON_NOESC) {
			zfcp_erp_port_block(port, 0);
			result = ZFCP_ERP_EXIT;
		}
		atomic_inc(&port->erp_counter);
		if (atomic_read(&port->erp_counter) > ZFCP_MAX_ERPS) {
			dev_err(&port->adapter->ccw_device->dev,
				"ERP failed for remote port 0x%016Lx\n",
				(unsigned long long)port->wwpn);
			zfcp_erp_port_failed(port, "erpsck1", NULL);
		}
		break;
	}

	if (atomic_read(&port->status) & ZFCP_STATUS_COMMON_ERP_FAILED) {
		zfcp_erp_port_block(port, 0);
		result = ZFCP_ERP_EXIT;
	}
	return result;
}