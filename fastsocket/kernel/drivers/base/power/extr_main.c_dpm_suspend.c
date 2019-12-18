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
struct list_head {struct list_head* prev; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct device {TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPM_OFF ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int device_suspend (struct device*,int /*<<< orphan*/ ) ; 
 struct list_head dpm_list ; 
 int /*<<< orphan*/  dpm_list_mtx ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  list_splice (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_dev_err (struct device*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct device* to_device (struct list_head*) ; 

__attribute__((used)) static int dpm_suspend(pm_message_t state)
{
	struct list_head list, *entry;
	int error = 0;

	INIT_LIST_HEAD(&list);
	mutex_lock(&dpm_list_mtx);
	while (!list_empty(&dpm_list)) {
		struct device *dev = to_device(dpm_list.prev);
		entry = dpm_list.prev;

		get_device(dev);
		mutex_unlock(&dpm_list_mtx);

		error = device_suspend(dev, state);

		mutex_lock(&dpm_list_mtx);
		if (error) {
			pm_dev_err(dev, state, "", error);
			put_device(dev);
			break;
		}
		dev->power.status = DPM_OFF;
		if (!list_empty(entry))
			list_move(entry, &list);
		put_device(dev);
	}
	list_splice(&list, dpm_list.prev);
	mutex_unlock(&dpm_list_mtx);
	return error;
}