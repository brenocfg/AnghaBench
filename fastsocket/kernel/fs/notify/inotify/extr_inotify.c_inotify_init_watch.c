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
struct inotify_watch {int /*<<< orphan*/  count; int /*<<< orphan*/  i_list; int /*<<< orphan*/  h_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_inotify_watch (struct inotify_watch*) ; 

void inotify_init_watch(struct inotify_watch *watch)
{
	INIT_LIST_HEAD(&watch->h_list);
	INIT_LIST_HEAD(&watch->i_list);
	atomic_set(&watch->count, 0);
	get_inotify_watch(watch); /* initial get */
}