#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct superblock_smack {char* smk_default; char* smk_root; } ;
struct super_block {int s_magic; struct superblock_smack* s_security; } ;
struct inode_smack {int smk_flags; char* smk_inode; int /*<<< orphan*/  smk_lock; } ;
struct inode {TYPE_1__* i_op; struct super_block* i_sb; struct inode_smack* i_security; } ;
struct dentry {struct dentry* d_parent; } ;
struct TYPE_4__ {char* smk_known; } ;
struct TYPE_3__ {int /*<<< orphan*/ * getxattr; } ;

/* Variables and functions */
#define  DEVPTS_SUPER_MAGIC 133 
#define  PIPEFS_MAGIC 132 
#define  PROC_SUPER_MAGIC 131 
#define  SMACK_MAGIC 130 
 int SMK_INODE_INSTANT ; 
#define  SOCKFS_MAGIC 129 
#define  TMPFS_MAGIC 128 
 char* current_security () ; 
 struct dentry* d_find_alias (struct inode*) ; 
 struct dentry* dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ smack_known_star ; 
 char* smk_fetch (struct inode*,struct dentry*) ; 

__attribute__((used)) static void smack_d_instantiate(struct dentry *opt_dentry, struct inode *inode)
{
	struct super_block *sbp;
	struct superblock_smack *sbsp;
	struct inode_smack *isp;
	char *csp = current_security();
	char *fetched;
	char *final;
	struct dentry *dp;

	if (inode == NULL)
		return;

	isp = inode->i_security;

	mutex_lock(&isp->smk_lock);
	/*
	 * If the inode is already instantiated
	 * take the quick way out
	 */
	if (isp->smk_flags & SMK_INODE_INSTANT)
		goto unlockandout;

	sbp = inode->i_sb;
	sbsp = sbp->s_security;
	/*
	 * We're going to use the superblock default label
	 * if there's no label on the file.
	 */
	final = sbsp->smk_default;

	/*
	 * If this is the root inode the superblock
	 * may be in the process of initialization.
	 * If that is the case use the root value out
	 * of the superblock.
	 */
	if (opt_dentry->d_parent == opt_dentry) {
		isp->smk_inode = sbsp->smk_root;
		isp->smk_flags |= SMK_INODE_INSTANT;
		goto unlockandout;
	}

	/*
	 * This is pretty hackish.
	 * Casey says that we shouldn't have to do
	 * file system specific code, but it does help
	 * with keeping it simple.
	 */
	switch (sbp->s_magic) {
	case SMACK_MAGIC:
		/*
		 * Casey says that it's a little embarassing
		 * that the smack file system doesn't do
		 * extended attributes.
		 */
		final = smack_known_star.smk_known;
		break;
	case PIPEFS_MAGIC:
		/*
		 * Casey says pipes are easy (?)
		 */
		final = smack_known_star.smk_known;
		break;
	case DEVPTS_SUPER_MAGIC:
		/*
		 * devpts seems content with the label of the task.
		 * Programs that change smack have to treat the
		 * pty with respect.
		 */
		final = csp;
		break;
	case SOCKFS_MAGIC:
		/*
		 * Casey says sockets get the smack of the task.
		 */
		final = csp;
		break;
	case PROC_SUPER_MAGIC:
		/*
		 * Casey says procfs appears not to care.
		 * The superblock default suffices.
		 */
		break;
	case TMPFS_MAGIC:
		/*
		 * Device labels should come from the filesystem,
		 * but watch out, because they're volitile,
		 * getting recreated on every reboot.
		 */
		final = smack_known_star.smk_known;
		/*
		 * No break.
		 *
		 * If a smack value has been set we want to use it,
		 * but since tmpfs isn't giving us the opportunity
		 * to set mount options simulate setting the
		 * superblock default.
		 */
	default:
		/*
		 * This isn't an understood special case.
		 * Get the value from the xattr.
		 *
		 * No xattr support means, alas, no SMACK label.
		 * Use the aforeapplied default.
		 * It would be curious if the label of the task
		 * does not match that assigned.
		 */
		if (inode->i_op->getxattr == NULL)
			break;
		/*
		 * Get the dentry for xattr.
		 */
		if (opt_dentry == NULL) {
			dp = d_find_alias(inode);
			if (dp == NULL)
				break;
		} else {
			dp = dget(opt_dentry);
			if (dp == NULL)
				break;
		}

		fetched = smk_fetch(inode, dp);
		if (fetched != NULL)
			final = fetched;

		dput(dp);
		break;
	}

	if (final == NULL)
		isp->smk_inode = csp;
	else
		isp->smk_inode = final;

	isp->smk_flags |= SMK_INODE_INSTANT;

unlockandout:
	mutex_unlock(&isp->smk_lock);
	return;
}