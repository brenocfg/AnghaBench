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
struct inotify_watch {int /*<<< orphan*/  wd; } ;
struct inotify_handle {TYPE_1__* in_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* handle_event ) (struct inotify_watch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IN_IGNORED ; 
 int /*<<< orphan*/  remove_watch_no_event (struct inotify_watch*,struct inotify_handle*) ; 
 int /*<<< orphan*/  stub1 (struct inotify_watch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void inotify_remove_watch_locked(struct inotify_handle *ih,
				 struct inotify_watch *watch)
{
	remove_watch_no_event(watch, ih);
	ih->in_ops->handle_event(watch, watch->wd, IN_IGNORED, 0, NULL, NULL);
}