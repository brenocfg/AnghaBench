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
struct audit_watch {TYPE_1__* parent; int /*<<< orphan*/  wlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  wdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_put_watch (struct audit_watch*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_inotify_watch (int /*<<< orphan*/ *) ; 

void audit_remove_watch(struct audit_watch *watch)
{
	list_del(&watch->wlist);
	put_inotify_watch(&watch->parent->wdata);
	watch->parent = NULL;
	audit_put_watch(watch); /* match initial get */
}