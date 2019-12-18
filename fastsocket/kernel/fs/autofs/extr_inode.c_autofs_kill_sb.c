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
struct super_block {int /*<<< orphan*/  s_fs_info; } ;
struct autofs_sb_info {TYPE_1__* symlink; int /*<<< orphan*/  symlink_bitmap; int /*<<< orphan*/  oz_pgrp; int /*<<< orphan*/  catatonic; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 unsigned int AUTOFS_MAX_SYMLINKS ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  autofs_catatonic_mode (struct autofs_sb_info*) ; 
 int /*<<< orphan*/  autofs_hash_nuke (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (struct super_block*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_anon_super (struct super_block*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

void autofs_kill_sb(struct super_block *sb)
{
	struct autofs_sb_info *sbi = autofs_sbi(sb);
	unsigned int n;

	/*
	 * In the event of a failure in get_sb_nodev the superblock
	 * info is not present so nothing else has been setup, so
	 * just call kill_anon_super when we are called from
	 * deactivate_super.
	 */
	if (!sbi)
		goto out_kill_sb;

	if (!sbi->catatonic)
		autofs_catatonic_mode(sbi); /* Free wait queues, close pipe */

	put_pid(sbi->oz_pgrp);

	autofs_hash_nuke(sbi);
	for (n = 0; n < AUTOFS_MAX_SYMLINKS; n++) {
		if (test_bit(n, sbi->symlink_bitmap))
			kfree(sbi->symlink[n].data);
	}

	kfree(sb->s_fs_info);

out_kill_sb:
	DPRINTK(("autofs: shutting down\n"));
	kill_anon_super(sb);
}