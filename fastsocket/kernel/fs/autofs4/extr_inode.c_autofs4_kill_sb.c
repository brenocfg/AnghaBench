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
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct autofs_sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  autofs4_catatonic_mode (struct autofs_sb_info*) ; 
 int /*<<< orphan*/  autofs4_force_release (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs4_sbi (struct super_block*) ; 
 int /*<<< orphan*/  kfree (struct autofs_sb_info*) ; 
 int /*<<< orphan*/  kill_anon_super (struct super_block*) ; 

void autofs4_kill_sb(struct super_block *sb)
{
	struct autofs_sb_info *sbi = autofs4_sbi(sb);

	/*
	 * In the event of a failure in get_sb_nodev the superblock
	 * info is not present so nothing else has been setup, so
	 * just call kill_anon_super when we are called from
	 * deactivate_super.
	 */
	if (!sbi)
		goto out_kill_sb;

	/* Free wait queues, close pipe */
	autofs4_catatonic_mode(sbi);

	/* Clean up and release dangling references */
	autofs4_force_release(sbi);

	sb->s_fs_info = NULL;
	kfree(sbi);

out_kill_sb:
	DPRINTK("shutting down");
	kill_anon_super(sb);
}