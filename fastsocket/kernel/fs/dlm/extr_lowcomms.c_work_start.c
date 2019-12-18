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

/* Variables and functions */
 int IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_print (char*,int) ; 
 int /*<<< orphan*/  recv_workqueue ; 
 int /*<<< orphan*/  send_workqueue ; 

__attribute__((used)) static int work_start(void)
{
	int error;
	recv_workqueue = create_singlethread_workqueue("dlm_recv");
	error = IS_ERR(recv_workqueue);
	if (error) {
		log_print("can't start dlm_recv %d", error);
		return error;
	}

	send_workqueue = create_singlethread_workqueue("dlm_send");
	error = IS_ERR(send_workqueue);
	if (error) {
		log_print("can't start dlm_send %d", error);
		destroy_workqueue(recv_workqueue);
		return error;
	}

	return 0;
}