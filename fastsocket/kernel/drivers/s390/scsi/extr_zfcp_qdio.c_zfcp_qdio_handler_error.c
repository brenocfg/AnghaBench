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
struct zfcp_qdio {struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {TYPE_1__* ccw_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int QDIO_ERROR_SLSB_STATE ; 
 int ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_shutdown (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_qdio_siosl (struct zfcp_adapter*) ; 

__attribute__((used)) static void zfcp_qdio_handler_error(struct zfcp_qdio *qdio, char *id,
				    unsigned int qdio_err)
{
	struct zfcp_adapter *adapter = qdio->adapter;

	dev_warn(&adapter->ccw_device->dev, "A QDIO problem occurred\n");

	if (qdio_err & QDIO_ERROR_SLSB_STATE) {
		zfcp_qdio_siosl(adapter);
		zfcp_erp_adapter_shutdown(adapter, 0, id, NULL);
		return;
	}
	zfcp_erp_adapter_reopen(adapter,
				ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED |
				ZFCP_STATUS_COMMON_ERP_FAILED, id, NULL);
}