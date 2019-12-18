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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct dentry {TYPE_1__* d_parent; int /*<<< orphan*/  d_fsdata; } ;
struct TYPE_4__ {scalar_t__ ip_blkno; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 TYPE_2__* OCFS2_I (struct inode*) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 

__attribute__((used)) static int ocfs2_match_dentry(struct dentry *dentry,
			      u64 parent_blkno,
			      int skip_unhashed)
{
	struct inode *parent;

	/*
	 * ocfs2_lookup() does a d_splice_alias() _before_ attaching
	 * to the lock data, so we skip those here, otherwise
	 * ocfs2_dentry_attach_lock() will get its original dentry
	 * back.
	 */
	if (!dentry->d_fsdata)
		return 0;

	if (!dentry->d_parent)
		return 0;

	if (skip_unhashed && d_unhashed(dentry))
		return 0;

	parent = dentry->d_parent->d_inode;
	/* Negative parent dentry? */
	if (!parent)
		return 0;

	/* Name is in a different directory. */
	if (OCFS2_I(parent)->ip_blkno != parent_blkno)
		return 0;

	return 1;
}