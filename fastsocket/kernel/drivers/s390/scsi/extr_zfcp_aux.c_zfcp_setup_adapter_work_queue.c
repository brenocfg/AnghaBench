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
struct zfcp_adapter {int /*<<< orphan*/  work_queue; TYPE_1__* ccw_device; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int TASK_COMM_LEN ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int zfcp_setup_adapter_work_queue(struct zfcp_adapter *adapter)
{
	char name[TASK_COMM_LEN];

	snprintf(name, sizeof(name), "zfcp_q_%s",
		 dev_name(&adapter->ccw_device->dev));
	adapter->work_queue = create_singlethread_workqueue(name);

	if (adapter->work_queue)
		return 0;
	return -ENOMEM;
}