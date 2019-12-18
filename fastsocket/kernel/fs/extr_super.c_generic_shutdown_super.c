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
struct super_operations {int /*<<< orphan*/  (* put_super ) (struct super_block*) ;} ;
struct super_block {int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_instances; int /*<<< orphan*/  s_list; int /*<<< orphan*/  s_id; int /*<<< orphan*/  s_flags; scalar_t__ s_root; struct super_operations* s_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_ACTIVE ; 
 int /*<<< orphan*/  get_fs_excl () ; 
 scalar_t__ invalidate_inodes (struct super_block*,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_fs_excl () ; 
 int /*<<< orphan*/  sb_lock ; 
 int /*<<< orphan*/  shrink_dcache_for_umount (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct super_block*) ; 
 int /*<<< orphan*/  sync_filesystem (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void generic_shutdown_super(struct super_block *sb)
{
	const struct super_operations *sop = sb->s_op;


	if (sb->s_root) {
		shrink_dcache_for_umount(sb);
		sync_filesystem(sb);
		get_fs_excl();
		sb->s_flags &= ~MS_ACTIVE;

		/* bad name - it should be evict_inodes() */
		invalidate_inodes(sb, true);

		if (sop->put_super)
			sop->put_super(sb);

		/* Forget any remaining inodes */
		if (invalidate_inodes(sb, true)) {
			printk("VFS: Busy inodes after unmount of %s. "
			   "Self-destruct in 5 seconds.  Have a nice day...\n",
			   sb->s_id);
		}
		put_fs_excl();
	}
	spin_lock(&sb_lock);
	/* should be initialized for __put_super_and_need_restart() */
	list_del_init(&sb->s_list);
	list_del(&sb->s_instances);
	spin_unlock(&sb_lock);
	up_write(&sb->s_umount);
}