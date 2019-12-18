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
struct inotify_watch {TYPE_1__* ih; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_inotify_watch (struct inotify_watch*) ; 
 int /*<<< orphan*/  inotify_remove_watch_locked (TYPE_1__*,struct inotify_watch*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void inotify_evict_watch(struct inotify_watch *watch)
{
	get_inotify_watch(watch);
	mutex_lock(&watch->ih->mutex);
	inotify_remove_watch_locked(watch->ih, watch);
	mutex_unlock(&watch->ih->mutex);
}