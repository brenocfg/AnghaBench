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
struct fsnotify_event {scalar_t__ data_type; int /*<<< orphan*/  file_name; int /*<<< orphan*/  private_data_list; int /*<<< orphan*/  path; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ FSNOTIFY_EVENT_PATH ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_event_cachep ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fsnotify_event*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 

void fsnotify_put_event(struct fsnotify_event *event)
{
	if (!event)
		return;

	if (atomic_dec_and_test(&event->refcnt)) {
		if (event->data_type == FSNOTIFY_EVENT_PATH)
			path_put(&event->path);

		BUG_ON(!list_empty(&event->private_data_list));

		kfree(event->file_name);
		kmem_cache_free(fsnotify_event_cachep, event);
	}
}