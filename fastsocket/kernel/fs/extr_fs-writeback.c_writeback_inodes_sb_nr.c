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
struct wb_writeback_work {unsigned long nr_pages; int /*<<< orphan*/ * done; int /*<<< orphan*/  sync_mode; struct super_block* sb; } ;
struct super_block {int /*<<< orphan*/  s_bdi; int /*<<< orphan*/  s_umount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WB_SYNC_NONE ; 
 int /*<<< orphan*/  bdi_queue_work (int /*<<< orphan*/ ,struct wb_writeback_work*) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void writeback_inodes_sb_nr(struct super_block *sb, unsigned long nr)
{
	DECLARE_COMPLETION_ONSTACK(done);
	struct wb_writeback_work work = {
		.sb		= sb,
		.sync_mode	= WB_SYNC_NONE,
		.done		= &done,
		.nr_pages	= nr,
	};

	WARN_ON(!rwsem_is_locked(&sb->s_umount));
	bdi_queue_work(sb->s_bdi, &work);
	wait_for_completion(&done);
}