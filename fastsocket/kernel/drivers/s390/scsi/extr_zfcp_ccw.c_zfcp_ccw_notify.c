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
struct zfcp_adapter {TYPE_1__* ccw_device; int /*<<< orphan*/  dbf; int /*<<< orphan*/  status; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CIO_BOXED 131 
#define  CIO_GONE 130 
#define  CIO_NO_PATH 129 
#define  CIO_OPER 128 
 int /*<<< orphan*/  ZFCP_SET ; 
 int ZFCP_STATUS_ADAPTER_SUSPENDED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_RUNNING ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct zfcp_adapter* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_base (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_shutdown (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_modify_adapter_status (struct zfcp_adapter*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_ccw_notify(struct ccw_device *ccw_device, int event)
{
	struct zfcp_adapter *adapter = dev_get_drvdata(&ccw_device->dev);

	switch (event) {
	case CIO_GONE:
		if (atomic_read(&adapter->status) &
		    ZFCP_STATUS_ADAPTER_SUSPENDED) { /* notification ignore */
			zfcp_dbf_hba_base(adapter->dbf, "nigo");
			break;
		}
		dev_warn(&adapter->ccw_device->dev,
			 "The FCP device has been detached\n");
		zfcp_erp_adapter_shutdown(adapter, 0, "ccnoti1", NULL);
		break;
	case CIO_NO_PATH:
		dev_warn(&adapter->ccw_device->dev,
			 "The CHPID for the FCP device is offline\n");
		zfcp_erp_adapter_shutdown(adapter, 0, "ccnoti2", NULL);
		break;
	case CIO_OPER:
		if (atomic_read(&adapter->status) &
		    ZFCP_STATUS_ADAPTER_SUSPENDED) { /* notification ignore */
			zfcp_dbf_hba_base(adapter->dbf, "niop");
			break;
		}
		dev_info(&adapter->ccw_device->dev,
			 "The FCP device is operational again\n");
		zfcp_erp_modify_adapter_status(adapter, "ccnoti3", NULL,
					       ZFCP_STATUS_COMMON_RUNNING,
					       ZFCP_SET);
		zfcp_erp_adapter_reopen(adapter, ZFCP_STATUS_COMMON_ERP_FAILED,
					"ccnoti4", NULL);
		break;
	case CIO_BOXED:
		dev_warn(&adapter->ccw_device->dev, "The FCP device "
			 "did not respond within the specified time\n");
		zfcp_erp_adapter_shutdown(adapter, 0, "ccnoti5", NULL);
		break;
	}
	return 1;
}