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
struct file_lock {int /*<<< orphan*/  fl_link; int /*<<< orphan*/  fl_block; int /*<<< orphan*/  fl_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  filelock_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct file_lock*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locks_release_private (struct file_lock*) ; 
 int waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void locks_free_lock(struct file_lock *fl)
{
	BUG_ON(waitqueue_active(&fl->fl_wait));
	BUG_ON(!list_empty(&fl->fl_block));
	BUG_ON(!list_empty(&fl->fl_link));

	locks_release_private(fl);
	kmem_cache_free(filelock_cache, fl);
}