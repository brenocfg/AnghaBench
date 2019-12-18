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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAKE_LOCK_SUSPEND ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ initialized ; 
 int /*<<< orphan*/  local_endpoints ; 
 int /*<<< orphan*/  msm_rpcrouter_exit_devices () ; 
 int msm_rpcrouter_init_devices () ; 
 int /*<<< orphan*/  newserver_wait ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_endpoints ; 
 int /*<<< orphan*/  rpcrouter_smdnotify ; 
 int /*<<< orphan*/  rpcrouter_wake_lock ; 
 int /*<<< orphan*/  rpcrouter_workqueue ; 
 int /*<<< orphan*/  smd_channel ; 
 int smd_open (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smd_wait ; 
 int /*<<< orphan*/  wake_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  work_read_data ; 

__attribute__((used)) static int msm_rpcrouter_probe(struct platform_device *pdev)
{
	int rc;

	/* Initialize what we need to start processing */
	INIT_LIST_HEAD(&local_endpoints);
	INIT_LIST_HEAD(&remote_endpoints);

	init_waitqueue_head(&newserver_wait);
	init_waitqueue_head(&smd_wait);
	wake_lock_init(&rpcrouter_wake_lock, WAKE_LOCK_SUSPEND, "SMD_RPCCALL");

	rpcrouter_workqueue = create_singlethread_workqueue("rpcrouter");
	if (!rpcrouter_workqueue)
		return -ENOMEM;

	rc = msm_rpcrouter_init_devices();
	if (rc < 0)
		goto fail_destroy_workqueue;

	/* Open up SMD channel 2 */
	initialized = 0;
	rc = smd_open("SMD_RPCCALL", &smd_channel, NULL, rpcrouter_smdnotify);
	if (rc < 0)
		goto fail_remove_devices;

	queue_work(rpcrouter_workqueue, &work_read_data);
	return 0;

 fail_remove_devices:
	msm_rpcrouter_exit_devices();
 fail_destroy_workqueue:
	destroy_workqueue(rpcrouter_workqueue);
	return rc;
}