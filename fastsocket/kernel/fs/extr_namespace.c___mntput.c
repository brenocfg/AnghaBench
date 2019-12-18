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
struct vfsmount {int /*<<< orphan*/  mnt_root; struct super_block* mnt_sb; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_mnt_writers (struct vfsmount*) ; 
 int /*<<< orphan*/  deactivate_super (struct super_block*) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_vfsmnt (struct vfsmount*) ; 

__attribute__((used)) static inline void __mntput(struct vfsmount *mnt)
{
	struct super_block *sb = mnt->mnt_sb;
	/*
	 * This probably indicates that somebody messed
	 * up a mnt_want/drop_write() pair.  If this
	 * happens, the filesystem was probably unable
	 * to make r/w->r/o transitions.
	 */
	/*
	 * atomic_dec_and_lock() used to deal with ->mnt_count decrements
	 * provides barriers, so count_mnt_writers() below is safe.  AV
	 */
	WARN_ON(count_mnt_writers(mnt));
	dput(mnt->mnt_root);
	free_vfsmnt(mnt);
	deactivate_super(sb);
}