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
struct zfcp_adapter {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  config_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_SET ; 
 int /*<<< orphan*/  ZFCP_STATUS_ADAPTER_SUSPENDED ; 
 struct zfcp_adapter* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_erp_adapter_shutdown (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_modify_adapter_status (struct zfcp_adapter*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 

__attribute__((used)) static int zfcp_ccw_suspend(struct ccw_device *cdev)

{
	struct zfcp_adapter *adapter = dev_get_drvdata(&cdev->dev);

	if (!adapter)
		return 0;

	mutex_lock(&zfcp_data.config_mutex);

	zfcp_erp_modify_adapter_status(adapter, "ccsusp2", NULL,
				       ZFCP_STATUS_ADAPTER_SUSPENDED, ZFCP_SET);
	zfcp_erp_adapter_shutdown(adapter, 0, "ccsusp1", NULL);
	zfcp_erp_wait(adapter);

	mutex_unlock(&zfcp_data.config_mutex);

	return 0;
}