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
typedef  void* u32 ;
struct superblock_security_struct {int flags; int /*<<< orphan*/  lock; void* mntpoint_sid; void* sid; int /*<<< orphan*/  behavior; int /*<<< orphan*/  def_sid; int /*<<< orphan*/  list; } ;
struct super_block {TYPE_1__* s_root; struct superblock_security_struct* s_security; } ;
struct inode_security_struct {void* sid; } ;
struct inode {struct inode_security_struct* i_security; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CONTEXT_MNT ; 
 int FSCONTEXT_MNT ; 
 int ROOTCONTEXT_MNT ; 
 int SE_SBINITIALIZED ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_finish_set_opts (struct super_block*) ; 
 int /*<<< orphan*/  sb_security_lock ; 
 int selinux_cmp_sb_context (struct super_block const*,struct super_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ss_initialized ; 
 int /*<<< orphan*/  superblock_security_head ; 

__attribute__((used)) static int selinux_sb_clone_mnt_opts(const struct super_block *oldsb,
					struct super_block *newsb)
{
	const struct superblock_security_struct *oldsbsec = oldsb->s_security;
	struct superblock_security_struct *newsbsec = newsb->s_security;

	int set_fscontext =	(oldsbsec->flags & FSCONTEXT_MNT);
	int set_context =	(oldsbsec->flags & CONTEXT_MNT);
	int set_rootcontext =	(oldsbsec->flags & ROOTCONTEXT_MNT);

	/*
	 * if the parent was able to be mounted it clearly had no special lsm
	 * mount options.  thus we can safely put this sb on the list and deal
	 * with it later
	 */
	if (!ss_initialized) {
		spin_lock(&sb_security_lock);
		if (list_empty(&newsbsec->list))
			list_add(&newsbsec->list, &superblock_security_head);
		spin_unlock(&sb_security_lock);
		return 0;
	}

	/* how can we clone if the old one wasn't set up?? */
	BUG_ON(!(oldsbsec->flags & SE_SBINITIALIZED));

	/* if fs is reusing a sb, make sure that the contexts match */
	if (newsbsec->flags & SE_SBINITIALIZED)
		return selinux_cmp_sb_context(oldsb, newsb);

	mutex_lock(&newsbsec->lock);

	newsbsec->flags = oldsbsec->flags;

	newsbsec->sid = oldsbsec->sid;
	newsbsec->def_sid = oldsbsec->def_sid;
	newsbsec->behavior = oldsbsec->behavior;

	if (set_context) {
		u32 sid = oldsbsec->mntpoint_sid;

		if (!set_fscontext)
			newsbsec->sid = sid;
		if (!set_rootcontext) {
			struct inode *newinode = newsb->s_root->d_inode;
			struct inode_security_struct *newisec = newinode->i_security;
			newisec->sid = sid;
		}
		newsbsec->mntpoint_sid = sid;
	}
	if (set_rootcontext) {
		const struct inode *oldinode = oldsb->s_root->d_inode;
		const struct inode_security_struct *oldisec = oldinode->i_security;
		struct inode *newinode = newsb->s_root->d_inode;
		struct inode_security_struct *newisec = newinode->i_security;

		newisec->sid = oldisec->sid;
	}

	sb_finish_set_opts(newsb);
	mutex_unlock(&newsbsec->lock);
	return 0;
}