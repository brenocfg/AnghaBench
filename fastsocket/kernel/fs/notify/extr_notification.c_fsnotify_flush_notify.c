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
struct fsnotify_group {int /*<<< orphan*/  notification_mutex; TYPE_1__* ops; } ;
struct fsnotify_event_private_data {int dummy; } ;
struct fsnotify_event {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_event_priv ) (struct fsnotify_event_private_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fsnotify_notify_queue_is_empty (struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_put_event (struct fsnotify_event*) ; 
 struct fsnotify_event* fsnotify_remove_notify_event (struct fsnotify_group*) ; 
 struct fsnotify_event_private_data* fsnotify_remove_priv_from_event (struct fsnotify_group*,struct fsnotify_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fsnotify_event_private_data*) ; 

void fsnotify_flush_notify(struct fsnotify_group *group)
{
	struct fsnotify_event *event;
	struct fsnotify_event_private_data *priv;

	mutex_lock(&group->notification_mutex);
	while (!fsnotify_notify_queue_is_empty(group)) {
		event = fsnotify_remove_notify_event(group);
		/* if they don't implement free_event_priv they better not have attached any */
		if (group->ops->free_event_priv) {
			spin_lock(&event->lock);
			priv = fsnotify_remove_priv_from_event(group, event);
			spin_unlock(&event->lock);
			if (priv)
				group->ops->free_event_priv(priv);
		}
		fsnotify_put_event(event); /* matches fsnotify_add_notify_event */
	}
	mutex_unlock(&group->notification_mutex);
}