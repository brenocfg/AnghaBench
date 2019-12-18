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
struct file_lock {int /*<<< orphan*/  fl_link; struct file_lock* fl_next; int /*<<< orphan*/  fl_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_POSIX (struct file_lock*) ; 
 int /*<<< orphan*/  blocked_list ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void locks_insert_block(struct file_lock *blocker, 
			       struct file_lock *waiter)
{
	BUG_ON(!list_empty(&waiter->fl_block));
	list_add_tail(&waiter->fl_block, &blocker->fl_block);
	waiter->fl_next = blocker;
	if (IS_POSIX(blocker))
		list_add(&waiter->fl_link, &blocked_list);
}