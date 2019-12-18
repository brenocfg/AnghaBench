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
struct list_head {struct list_head* next; } ;
struct TYPE_2__ {scalar_t__ status; } ;
struct device {TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 scalar_t__ DPM_OFF ; 
 void* DPM_RESUMING ; 
 scalar_t__ DPM_SUSPENDING ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int device_resume (struct device*,int /*<<< orphan*/ ) ; 
 struct list_head dpm_list ; 
 int /*<<< orphan*/  dpm_list_mtx ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move_tail (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  list_splice (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_dev_err (struct device*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct device* to_device (struct list_head*) ; 

__attribute__((used)) static void dpm_resume(pm_message_t state)
{
	struct list_head list;
	struct list_head *entry;

	INIT_LIST_HEAD(&list);
	mutex_lock(&dpm_list_mtx);
	while (!list_empty(&dpm_list)) {
		struct device *dev = to_device(dpm_list.next);
		entry = dpm_list.next;

		get_device(dev);
		if (dev->power.status >= DPM_OFF) {
			int error;

			dev->power.status = DPM_RESUMING;
			mutex_unlock(&dpm_list_mtx);

			error = device_resume(dev, state);

			mutex_lock(&dpm_list_mtx);
			if (error)
				pm_dev_err(dev, state, "", error);
		} else if (dev->power.status == DPM_SUSPENDING) {
			/* Allow new children of the device to be registered */
			dev->power.status = DPM_RESUMING;
		}
		if (!list_empty(entry))
			list_move_tail(entry, &list);
		put_device(dev);
	}
	list_splice(&list, &dpm_list);
	mutex_unlock(&dpm_list_mtx);
}