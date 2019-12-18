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
struct work_struct {int dummy; } ;
struct edac_device_ctl_info {scalar_t__ op_state; int poll_msec; int /*<<< orphan*/  delay; int /*<<< orphan*/  work; int /*<<< orphan*/  (* edac_check ) (struct edac_device_ctl_info*) ;} ;
struct delayed_work {int dummy; } ;

/* Variables and functions */
 scalar_t__ OP_OFFLINE ; 
 scalar_t__ OP_RUNNING_POLL ; 
 int /*<<< orphan*/  device_ctls_mutex ; 
 int /*<<< orphan*/  edac_workqueue ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct edac_device_ctl_info*) ; 
 struct delayed_work* to_delayed_work (struct work_struct*) ; 
 struct edac_device_ctl_info* to_edac_device_ctl_work (struct delayed_work*) ; 

__attribute__((used)) static void edac_device_workq_function(struct work_struct *work_req)
{
	struct delayed_work *d_work = to_delayed_work(work_req);
	struct edac_device_ctl_info *edac_dev = to_edac_device_ctl_work(d_work);

	mutex_lock(&device_ctls_mutex);

	/* If we are being removed, bail out immediately */
	if (edac_dev->op_state == OP_OFFLINE) {
		mutex_unlock(&device_ctls_mutex);
		return;
	}

	/* Only poll controllers that are running polled and have a check */
	if ((edac_dev->op_state == OP_RUNNING_POLL) &&
		(edac_dev->edac_check != NULL)) {
			edac_dev->edac_check(edac_dev);
	}

	mutex_unlock(&device_ctls_mutex);

	/* Reschedule the workq for the next time period to start again
	 * if the number of msec is for 1 sec, then adjust to the next
	 * whole one second to save timers fireing all over the period
	 * between integral seconds
	 */
	if (edac_dev->poll_msec == 1000)
		queue_delayed_work(edac_workqueue, &edac_dev->work,
				round_jiffies_relative(edac_dev->delay));
	else
		queue_delayed_work(edac_workqueue, &edac_dev->work,
				edac_dev->delay);
}