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
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ap_poll_kthread ; 
 int /*<<< orphan*/  ap_poll_thread ; 
 int /*<<< orphan*/  ap_poll_thread_mutex ; 
 scalar_t__ ap_suspend_flag ; 
 scalar_t__ ap_using_interrupts () ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ap_poll_thread_start(void)
{
	int rc;

	if (ap_using_interrupts() || ap_suspend_flag)
		return 0;
	mutex_lock(&ap_poll_thread_mutex);
	if (!ap_poll_kthread) {
		ap_poll_kthread = kthread_run(ap_poll_thread, NULL, "appoll");
		rc = IS_ERR(ap_poll_kthread) ? PTR_ERR(ap_poll_kthread) : 0;
		if (rc)
			ap_poll_kthread = NULL;
	}
	else
		rc = 0;
	mutex_unlock(&ap_poll_thread_mutex);
	return rc;
}