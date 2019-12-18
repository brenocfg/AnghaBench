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
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  polldev_mutex ; 
 int /*<<< orphan*/  polldev_users ; 
 int /*<<< orphan*/  polldev_wq ; 

__attribute__((used)) static void input_polldev_stop_workqueue(void)
{
	mutex_lock(&polldev_mutex);

	if (!--polldev_users)
		destroy_workqueue(polldev_wq);

	mutex_unlock(&polldev_mutex);
}