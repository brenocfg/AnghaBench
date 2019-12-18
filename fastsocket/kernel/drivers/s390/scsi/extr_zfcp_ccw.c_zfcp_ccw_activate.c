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
struct zfcp_adapter {int /*<<< orphan*/  scan_work; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_CLEAR ; 
 int /*<<< orphan*/  ZFCP_SET ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int ZFCP_STATUS_COMMON_RUNNING ; 
 struct zfcp_adapter* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_modify_adapter_status (struct zfcp_adapter*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 

__attribute__((used)) static int zfcp_ccw_activate(struct ccw_device *cdev, int clear, char *tag)
{
	struct zfcp_adapter *adapter = dev_get_drvdata(&cdev->dev);

	if (!adapter)
		return 0;

	zfcp_erp_modify_adapter_status(adapter, tag, NULL, clear, ZFCP_CLEAR);
	zfcp_erp_modify_adapter_status(adapter, tag, NULL,
				       ZFCP_STATUS_COMMON_RUNNING, ZFCP_SET);
	zfcp_erp_adapter_reopen(adapter, ZFCP_STATUS_COMMON_ERP_FAILED,
				tag, NULL);
	zfcp_erp_wait(adapter);
	flush_work(&adapter->scan_work); /* ok to call even if nothing queued */

	return 0;
}