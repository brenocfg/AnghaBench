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
struct wb_writeback_work {int /*<<< orphan*/ * done; int /*<<< orphan*/  range_cyclic; int /*<<< orphan*/  nr_pages; int /*<<< orphan*/  sync_mode; struct super_block* sb; } ;
struct super_block {int /*<<< orphan*/  s_bdi; int /*<<< orphan*/  s_umount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 int /*<<< orphan*/  bdi_queue_work (int /*<<< orphan*/ ,struct wb_writeback_work*) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_sb_inodes (struct super_block*) ; 

void sync_inodes_sb(struct super_block *sb)
{
	DECLARE_COMPLETION_ONSTACK(done);
	struct wb_writeback_work work = {
		.sb		= sb,
		.sync_mode	= WB_SYNC_ALL,
		.nr_pages	= LONG_MAX,
		.range_cyclic	= 0,
		.done		= &done,
	};

	WARN_ON(!rwsem_is_locked(&sb->s_umount));

	bdi_queue_work(sb->s_bdi, &work);
	wait_for_completion(&done);

	wait_sb_inodes(sb);
}