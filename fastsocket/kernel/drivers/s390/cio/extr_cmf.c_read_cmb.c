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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct cmb_data {struct cmb* last_block; } ;
struct cmb {int ssch_rsch_count; int sample_count; int /*<<< orphan*/  device_active_only_time; int /*<<< orphan*/  control_unit_queuing_time; int /*<<< orphan*/  device_disconnect_time; int /*<<< orphan*/  function_pending_time; int /*<<< orphan*/  device_connect_time; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_1__* private; } ;
struct TYPE_2__ {scalar_t__ cmb; } ;

/* Variables and functions */
#define  cmb_control_unit_queuing_time 134 
#define  cmb_device_active_only_time 133 
#define  cmb_device_connect_time 132 
#define  cmb_device_disconnect_time 131 
#define  cmb_function_pending_time 130 
#define  cmb_sample_count 129 
#define  cmb_ssch_rsch_count 128 
 int cmf_cmb_copy_wait (struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int time_to_avg_nsec (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u64 read_cmb(struct ccw_device *cdev, int index)
{
	struct cmb *cmb;
	u32 val;
	int ret;
	unsigned long flags;

	ret = cmf_cmb_copy_wait(cdev);
	if (ret < 0)
		return 0;

	spin_lock_irqsave(cdev->ccwlock, flags);
	if (!cdev->private->cmb) {
		ret = 0;
		goto out;
	}
	cmb = ((struct cmb_data *)cdev->private->cmb)->last_block;

	switch (index) {
	case cmb_ssch_rsch_count:
		ret = cmb->ssch_rsch_count;
		goto out;
	case cmb_sample_count:
		ret = cmb->sample_count;
		goto out;
	case cmb_device_connect_time:
		val = cmb->device_connect_time;
		break;
	case cmb_function_pending_time:
		val = cmb->function_pending_time;
		break;
	case cmb_device_disconnect_time:
		val = cmb->device_disconnect_time;
		break;
	case cmb_control_unit_queuing_time:
		val = cmb->control_unit_queuing_time;
		break;
	case cmb_device_active_only_time:
		val = cmb->device_active_only_time;
		break;
	default:
		ret = 0;
		goto out;
	}
	ret = time_to_avg_nsec(val, cmb->sample_count);
out:
	spin_unlock_irqrestore(cdev->ccwlock, flags);
	return ret;
}