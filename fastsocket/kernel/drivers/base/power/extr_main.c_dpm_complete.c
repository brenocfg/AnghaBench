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
struct TYPE_2__ {scalar_t__ status; } ;
struct device {TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 scalar_t__ DPM_ON ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  device_complete (struct device*,int /*<<< orphan*/ ) ; 
 struct list_head dpm_list ; 
 int /*<<< orphan*/  dpm_list_mtx ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  list_splice (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct device* to_device (struct list_head*) ; 
 int transition_started ; 

__attribute__((used)) static void dpm_complete(pm_message_t state)
{
	struct list_head list, *entry;

	INIT_LIST_HEAD(&list);
	mutex_lock(&dpm_list_mtx);
	transition_started = false;
	while (!list_empty(&dpm_list)) {
		struct device *dev = to_device(dpm_list.prev);
		entry = dpm_list.prev;

		get_device(dev);
		if (dev->power.status > DPM_ON) {
			dev->power.status = DPM_ON;
			mutex_unlock(&dpm_list_mtx);

			device_complete(dev, state);
			pm_runtime_put_noidle(dev);

			mutex_lock(&dpm_list_mtx);
		}
		if (!list_empty(entry))
			list_move(entry, &list);
		put_device(dev);
	}
	list_splice(&list, &dpm_list);
	mutex_unlock(&dpm_list_mtx);
}