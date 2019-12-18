#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct ap_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  qid; } ;
struct TYPE_4__ {scalar_t__ expires; scalar_t__ data; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_MKQID (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AP_QID_DEVICE (int /*<<< orphan*/ ) ; 
 int AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int ap_config_time ; 
 int /*<<< orphan*/  ap_config_timeout ; 
 TYPE_1__ ap_config_timer ; 
 int /*<<< orphan*/  ap_config_work ; 
 int ap_domain_index ; 
 int /*<<< orphan*/ * ap_interrupt_indicator ; 
 int /*<<< orphan*/  ap_interrupts_available () ; 
 int ap_poll_thread_start () ; 
 int /*<<< orphan*/  ap_query_configuration () ; 
 int /*<<< orphan*/  ap_schedule_poll_timer () ; 
 int /*<<< orphan*/  ap_select_domain () ; 
 scalar_t__ ap_suspend_flag ; 
 int /*<<< orphan*/  ap_tasklet ; 
 scalar_t__ ap_thread_flag ; 
 int /*<<< orphan*/  ap_using_interrupts () ; 
 int /*<<< orphan*/  ap_work_queue ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct ap_device* to_ap_dev (struct device*) ; 
 int /*<<< orphan*/  user_set_domain ; 

__attribute__((used)) static int ap_bus_resume(struct device *dev)
{
	int rc = 0;
	struct ap_device *ap_dev = to_ap_dev(dev);

	if (ap_suspend_flag) {
		ap_suspend_flag = 0;
		if (!ap_interrupts_available())
			ap_interrupt_indicator = NULL;
		ap_query_configuration();
		if (!user_set_domain) {
			ap_domain_index = -1;
			ap_select_domain();
		}
		init_timer(&ap_config_timer);
		ap_config_timer.function = ap_config_timeout;
		ap_config_timer.data = 0;
		ap_config_timer.expires = jiffies + ap_config_time * HZ;
		add_timer(&ap_config_timer);
		ap_work_queue = create_singlethread_workqueue("kapwork");
		if (!ap_work_queue)
			return -ENOMEM;
		tasklet_enable(&ap_tasklet);
		if (!ap_using_interrupts())
			ap_schedule_poll_timer();
		else
			tasklet_schedule(&ap_tasklet);
		if (ap_thread_flag)
			rc = ap_poll_thread_start();
	}
	if (AP_QID_QUEUE(ap_dev->qid) != ap_domain_index) {
		spin_lock_bh(&ap_dev->lock);
		ap_dev->qid = AP_MKQID(AP_QID_DEVICE(ap_dev->qid),
				       ap_domain_index);
		spin_unlock_bh(&ap_dev->lock);
	}
	queue_work(ap_work_queue, &ap_config_work);

	return rc;
}