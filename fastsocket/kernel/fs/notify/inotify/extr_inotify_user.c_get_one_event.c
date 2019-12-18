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
struct inotify_event {int dummy; } ;
struct fsnotify_group {int dummy; } ;
struct fsnotify_event {scalar_t__ name_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct fsnotify_event* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ fsnotify_notify_queue_is_empty (struct fsnotify_group*) ; 
 struct fsnotify_event* fsnotify_peek_notify_event (struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_remove_notify_event (struct fsnotify_group*) ; 
 scalar_t__ roundup (scalar_t__,size_t) ; 

__attribute__((used)) static struct fsnotify_event *get_one_event(struct fsnotify_group *group,
					    size_t count)
{
	size_t event_size = sizeof(struct inotify_event);
	struct fsnotify_event *event;

	if (fsnotify_notify_queue_is_empty(group))
		return NULL;

	event = fsnotify_peek_notify_event(group);

	if (event->name_len)
		event_size += roundup(event->name_len + 1, event_size);

	if (event_size > count)
		return ERR_PTR(-EINVAL);

	/* held the notification_mutex the whole time, so this is the
	 * same event we peeked above */
	fsnotify_remove_notify_event(group);

	return event;
}