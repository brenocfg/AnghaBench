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
struct file_lock {int /*<<< orphan*/ * fl_lmops; int /*<<< orphan*/ * fl_ops; scalar_t__ fl_end; scalar_t__ fl_start; scalar_t__ fl_type; scalar_t__ fl_flags; int /*<<< orphan*/ * fl_file; int /*<<< orphan*/ * fl_nspid; scalar_t__ fl_pid; int /*<<< orphan*/ * fl_owner; int /*<<< orphan*/ * fl_fasync; int /*<<< orphan*/ * fl_next; int /*<<< orphan*/  fl_wait; int /*<<< orphan*/  fl_block; int /*<<< orphan*/  fl_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

void locks_init_lock(struct file_lock *fl)
{
	INIT_LIST_HEAD(&fl->fl_link);
	INIT_LIST_HEAD(&fl->fl_block);
	init_waitqueue_head(&fl->fl_wait);
	fl->fl_next = NULL;
	fl->fl_fasync = NULL;
	fl->fl_owner = NULL;
	fl->fl_pid = 0;
	fl->fl_nspid = NULL;
	fl->fl_file = NULL;
	fl->fl_flags = 0;
	fl->fl_type = 0;
	fl->fl_start = fl->fl_end = 0;
	fl->fl_ops = NULL;
	fl->fl_lmops = NULL;
}