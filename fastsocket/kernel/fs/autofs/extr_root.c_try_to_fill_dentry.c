#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dentry {unsigned long d_time; int /*<<< orphan*/  d_flags; TYPE_1__ d_name; struct inode* d_inode; } ;
struct autofs_sb_info {int /*<<< orphan*/  dirhash; } ;
struct autofs_dir_ent {int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 unsigned long AUTOFS_NEGATIVE_TIMEOUT ; 
 int /*<<< orphan*/  DCACHE_AUTOFS_PENDING ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 struct autofs_dir_ent* autofs_hash_lookup (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct inode* autofs_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autofs_oz_mode (struct autofs_sb_info*) ; 
 int /*<<< orphan*/  autofs_update_usage (int /*<<< orphan*/ *,struct autofs_dir_ent*) ; 
 int autofs_wait (struct autofs_sb_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  d_mountpoint (struct dentry*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_to_fill_dentry(struct dentry *dentry, struct super_block *sb, struct autofs_sb_info *sbi)
{
	struct inode * inode;
	struct autofs_dir_ent *ent;
	int status = 0;

	if (!(ent = autofs_hash_lookup(&sbi->dirhash, &dentry->d_name))) {
		do {
			if (status && dentry->d_inode) {
				if (status != -ENOENT)
					printk("autofs warning: lookup failure on positive dentry, status = %d, name = %s\n", status, dentry->d_name.name);
				return 0; /* Try to get the kernel to invalidate this dentry */
			}

			/* Turn this into a real negative dentry? */
			if (status == -ENOENT) {
				dentry->d_time = jiffies + AUTOFS_NEGATIVE_TIMEOUT;
				dentry->d_flags &= ~DCACHE_AUTOFS_PENDING;
				return 1;
			} else if (status) {
				/* Return a negative dentry, but leave it "pending" */
				return 1;
			}
			status = autofs_wait(sbi, &dentry->d_name);
		} while (!(ent = autofs_hash_lookup(&sbi->dirhash, &dentry->d_name)));
	}

	/* Abuse this field as a pointer to the directory entry, used to
	   find the expire list pointers */
	dentry->d_time = (unsigned long) ent;
	
	if (!dentry->d_inode) {
		inode = autofs_iget(sb, ent->ino);
		if (IS_ERR(inode)) {
			/* Failed, but leave pending for next time */
			return 1;
		}
		dentry->d_inode = inode;
	}

	/* If this is a directory that isn't a mount point, bitch at the
	   daemon and fix it in user space */
	if (S_ISDIR(dentry->d_inode->i_mode) && !d_mountpoint(dentry)) {
		return !autofs_wait(sbi, &dentry->d_name);
	}

	/* We don't update the usages for the autofs daemon itself, this
	   is necessary for recursive autofs mounts */
	if (!autofs_oz_mode(sbi)) {
		autofs_update_usage(&sbi->dirhash,ent);
	}

	dentry->d_flags &= ~DCACHE_AUTOFS_PENDING;
	return 1;
}