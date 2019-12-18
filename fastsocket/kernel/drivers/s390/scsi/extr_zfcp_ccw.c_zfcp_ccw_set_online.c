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
struct zfcp_adapter {int /*<<< orphan*/  scan_work; scalar_t__ req_no; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  config_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ZFCP_SET ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_RUNNING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct zfcp_adapter* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int zfcp_adapter_enqueue (struct ccw_device*) ; 
 TYPE_1__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_modify_adapter_status (struct zfcp_adapter*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fc_inverse_conditional_port_scan (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_reqlist_isempty (struct zfcp_adapter*) ; 

__attribute__((used)) static int zfcp_ccw_set_online(struct ccw_device *ccw_device)
{
	struct zfcp_adapter *adapter;
	int ret = 0;

	mutex_lock(&zfcp_data.config_mutex);
	adapter = dev_get_drvdata(&ccw_device->dev);

	if (!adapter) {
		ret = zfcp_adapter_enqueue(ccw_device);
		if (ret) {
			dev_err(&ccw_device->dev,
				"Setting up data structures for the "
				"FCP adapter failed\n");
			goto out;
		}
		adapter = dev_get_drvdata(&ccw_device->dev);
	}

	/* initialize request counter */
	BUG_ON(!zfcp_reqlist_isempty(adapter));
	adapter->req_no = 0;

	zfcp_erp_modify_adapter_status(adapter, "ccsonl1", NULL,
				       ZFCP_STATUS_COMMON_RUNNING, ZFCP_SET);
	zfcp_erp_adapter_reopen(adapter, ZFCP_STATUS_COMMON_ERP_FAILED,
				"ccsonl2", NULL);
	zfcp_erp_wait(adapter);
	/* scan for remote ports
	   either at the end of any successful adapter recovery
	   or only after the adapter recovery for setting a device online */
	zfcp_fc_inverse_conditional_port_scan(adapter);
out:
	mutex_unlock(&zfcp_data.config_mutex);
	if (!ret)
		flush_work(&adapter->scan_work); /* ok even if nothing queued */
	return ret;
}