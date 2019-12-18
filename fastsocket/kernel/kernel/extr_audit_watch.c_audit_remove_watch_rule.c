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
struct list_head {int dummy; } ;
struct audit_watch {int /*<<< orphan*/  rules; struct audit_parent* parent; } ;
struct audit_parent {int /*<<< orphan*/  ilist; int /*<<< orphan*/  wdata; int /*<<< orphan*/  watches; } ;
struct audit_krule {int /*<<< orphan*/  rlist; struct audit_watch* watch; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_remove_watch (struct audit_watch*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ pin_inotify_watch (int /*<<< orphan*/ *) ; 

void audit_remove_watch_rule(struct audit_krule *krule, struct list_head *list)
{
	struct audit_watch *watch = krule->watch;
	struct audit_parent *parent = watch->parent;

	list_del(&krule->rlist);

	if (list_empty(&watch->rules)) {
		audit_remove_watch(watch);

		if (list_empty(&parent->watches)) {
			/* Put parent on the inotify un-registration
			 * list.  Grab a reference before releasing
			 * audit_filter_mutex, to be released in
			 * audit_inotify_unregister().
			 * If filesystem is going away, just leave
			 * the sucker alone, eviction will take
			 * care of it. */
			if (pin_inotify_watch(&parent->wdata))
				list_add(&parent->ilist, list);
		}
	}
}