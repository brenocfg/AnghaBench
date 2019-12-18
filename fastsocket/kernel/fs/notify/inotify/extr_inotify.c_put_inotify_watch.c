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
struct inotify_watch {int /*<<< orphan*/  inode; struct inotify_handle* ih; int /*<<< orphan*/  count; } ;
struct inotify_handle {TYPE_1__* in_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy_watch ) (struct inotify_watch*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_inotify_handle (struct inotify_handle*) ; 
 int /*<<< orphan*/  stub1 (struct inotify_watch*) ; 

void put_inotify_watch(struct inotify_watch *watch)
{
	if (atomic_dec_and_test(&watch->count)) {
		struct inotify_handle *ih = watch->ih;

		iput(watch->inode);
		ih->in_ops->destroy_watch(watch);
		put_inotify_handle(ih);
	}
}