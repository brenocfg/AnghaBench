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
typedef  scalar_t__ u64 ;
struct super_block {int dummy; } ;
struct ocfs2_super {struct super_block* sb; } ;
struct ocfs2_find_inode_args {unsigned int fi_flags; int fi_sysfile_type; int /*<<< orphan*/  fi_ino; scalar_t__ fi_blkno; } ;
struct inode {int i_state; } ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 int I_NEW ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  PTR_ERR (struct inode*) ; 
 struct inode* iget5_locked (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_find_inode_args*) ; 
 int /*<<< orphan*/  ino_from_blkno (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_exit_ptr (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_find_actor ; 
 int /*<<< orphan*/  ocfs2_init_locked_inode ; 
 int /*<<< orphan*/  ocfs2_read_locked_inode (struct inode*,struct ocfs2_find_inode_args*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *ocfs2_iget(struct ocfs2_super *osb, u64 blkno, unsigned flags,
			 int sysfile_type)
{
	struct inode *inode = NULL;
	struct super_block *sb = osb->sb;
	struct ocfs2_find_inode_args args;

	mlog_entry("(blkno = %llu)\n", (unsigned long long)blkno);

	/* Ok. By now we've either got the offsets passed to us by the
	 * caller, or we just pulled them off the bh. Lets do some
	 * sanity checks to make sure they're OK. */
	if (blkno == 0) {
		inode = ERR_PTR(-EINVAL);
		mlog_errno(PTR_ERR(inode));
		goto bail;
	}

	args.fi_blkno = blkno;
	args.fi_flags = flags;
	args.fi_ino = ino_from_blkno(sb, blkno);
	args.fi_sysfile_type = sysfile_type;

	inode = iget5_locked(sb, args.fi_ino, ocfs2_find_actor,
			     ocfs2_init_locked_inode, &args);
	/* inode was *not* in the inode cache. 2.6.x requires
	 * us to do our own read_inode call and unlock it
	 * afterwards. */
	if (inode && inode->i_state & I_NEW) {
		mlog(0, "Inode was not in inode cache, reading it.\n");
		ocfs2_read_locked_inode(inode, &args);
		unlock_new_inode(inode);
	}
	if (inode == NULL) {
		inode = ERR_PTR(-ENOMEM);
		mlog_errno(PTR_ERR(inode));
		goto bail;
	}
	if (is_bad_inode(inode)) {
		iput(inode);
		inode = ERR_PTR(-ESTALE);
		goto bail;
	}

bail:
	if (!IS_ERR(inode)) {
		mlog(0, "returning inode with number %llu\n",
		     (unsigned long long)OCFS2_I(inode)->ip_blkno);
		mlog_exit_ptr(inode);
	}

	return inode;
}