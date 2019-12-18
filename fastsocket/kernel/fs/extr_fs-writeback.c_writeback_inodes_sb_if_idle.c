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
struct super_block {int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_bdi; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeback_in_progress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeback_inodes_sb (struct super_block*) ; 

int writeback_inodes_sb_if_idle(struct super_block *sb)
{
	if (!writeback_in_progress(sb->s_bdi)) {
		down_read(&sb->s_umount);
		writeback_inodes_sb(sb);
		up_read(&sb->s_umount);
		return 1;
	} else
		return 0;
}