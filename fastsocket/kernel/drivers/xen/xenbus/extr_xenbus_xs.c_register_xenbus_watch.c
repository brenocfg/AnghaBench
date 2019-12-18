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
typedef  int /*<<< orphan*/  watch ;
struct xenbus_watch {int /*<<< orphan*/  list; int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  watch_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EEXIST ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_watch (char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watches ; 
 int /*<<< orphan*/  watches_lock ; 
 TYPE_1__ xs_state ; 
 int xs_watch (int /*<<< orphan*/ ,char*) ; 

int register_xenbus_watch(struct xenbus_watch *watch)
{
	/* Pointer in ascii is the token. */
	char token[sizeof(watch) * 2 + 1];
	int err;

	sprintf(token, "%lX", (long)watch);

	down_read(&xs_state.watch_mutex);

	spin_lock(&watches_lock);
	BUG_ON(find_watch(token));
	list_add(&watch->list, &watches);
	spin_unlock(&watches_lock);

	err = xs_watch(watch->node, token);

	/* Ignore errors due to multiple registration. */
	if ((err != 0) && (err != -EEXIST)) {
		spin_lock(&watches_lock);
		list_del(&watch->list);
		spin_unlock(&watches_lock);
	}

	up_read(&xs_state.watch_mutex);

	return err;
}