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
struct ibmvscsi_host_data {int /*<<< orphan*/  work_wait_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ibmvscsi_do_work (struct ibmvscsi_host_data*) ; 
 int /*<<< orphan*/  ibmvscsi_work_to_do (struct ibmvscsi_host_data*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvscsi_work(void *data)
{
	struct ibmvscsi_host_data *hostdata = data;
	int rc;

	set_user_nice(current, -20);

	while (1) {
		rc = wait_event_interruptible(hostdata->work_wait_q,
					      ibmvscsi_work_to_do(hostdata));

		BUG_ON(rc);

		if (kthread_should_stop())
			break;

		ibmvscsi_do_work(hostdata);
	}

	return 0;
}