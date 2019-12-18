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
struct super_block {int s_flags; } ;
struct jfs_sb_info {struct jfs_log* log; } ;
struct jfs_log {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_MOUNT ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  jfs_err (char*,int) ; 
 int lmLogInit (struct jfs_log*) ; 
 int /*<<< orphan*/  txResume (struct super_block*) ; 
 int /*<<< orphan*/  updateSuper (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jfs_unfreeze(struct super_block *sb)
{
	struct jfs_sb_info *sbi = JFS_SBI(sb);
	struct jfs_log *log = sbi->log;
	int rc = 0;

	if (!(sb->s_flags & MS_RDONLY)) {
		updateSuper(sb, FM_MOUNT);
		if ((rc = lmLogInit(log)))
			jfs_err("jfs_unlock failed with return code %d", rc);
		else
			txResume(sb);
	}
	return 0;
}