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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct super_block {struct exofs_sb_info* s_fs_info; scalar_t__ s_dirt; } ;
struct exofs_sb_info {int /*<<< orphan*/  s_dev; int /*<<< orphan*/  s_curr_pending; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exofs_write_super (struct super_block*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct exofs_sb_info*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  osduld_put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exofs_put_super(struct super_block *sb)
{
	int num_pend;
	struct exofs_sb_info *sbi = sb->s_fs_info;

	if (sb->s_dirt)
		exofs_write_super(sb);

	/* make sure there are no pending commands */
	for (num_pend = atomic_read(&sbi->s_curr_pending); num_pend > 0;
	     num_pend = atomic_read(&sbi->s_curr_pending)) {
		wait_queue_head_t wq;
		init_waitqueue_head(&wq);
		wait_event_timeout(wq,
				  (atomic_read(&sbi->s_curr_pending) == 0),
				  msecs_to_jiffies(100));
	}

	osduld_put_device(sbi->s_dev);
	kfree(sb->s_fs_info);
	sb->s_fs_info = NULL;
}