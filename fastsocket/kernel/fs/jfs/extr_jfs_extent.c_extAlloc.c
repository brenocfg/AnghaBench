#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_9__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flag; } ;
typedef  TYPE_1__ xad_t ;
struct jfs_sb_info {int l2nbperpage; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int s64 ;
struct TYPE_11__ {int /*<<< orphan*/  commit_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_Synclist ; 
 int EDQUOT ; 
 int INOHINT (struct inode*) ; 
 TYPE_9__* JFS_IP (struct inode*) ; 
 struct jfs_sb_info* JFS_SBI (int /*<<< orphan*/ ) ; 
 int MAXXLEN ; 
 int XAD_NOTRECORDED ; 
 int /*<<< orphan*/  XADaddress (TYPE_1__*,int) ; 
 int /*<<< orphan*/  XADlength (TYPE_1__*,int) ; 
 int /*<<< orphan*/  XADoffset (TYPE_1__*,int) ; 
 int addressXAD (TYPE_1__*) ; 
 int /*<<< orphan*/  dbFree (struct inode*,int,int) ; 
 int extBalloc (struct inode*,int,int*,int*) ; 
 int /*<<< orphan*/  jfs_commit_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int lengthXAD (TYPE_1__*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int offsetXAD (TYPE_1__*) ; 
 scalar_t__ test_and_clear_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  txBeginAnon (int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_dq_alloc_block (struct inode*,int) ; 
 int /*<<< orphan*/  vfs_dq_free_block (struct inode*,int) ; 
 int xtExtend (int /*<<< orphan*/ ,struct inode*,int,int,int /*<<< orphan*/ ) ; 
 int xtInsert (int /*<<< orphan*/ ,struct inode*,int,int,int,int*,int /*<<< orphan*/ ) ; 

int
extAlloc(struct inode *ip, s64 xlen, s64 pno, xad_t * xp, bool abnr)
{
	struct jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	s64 nxlen, nxaddr, xoff, hint, xaddr = 0;
	int rc;
	int xflag;

	/* This blocks if we are low on resources */
	txBeginAnon(ip->i_sb);

	/* Avoid race with jfs_commit_inode() */
	mutex_lock(&JFS_IP(ip)->commit_mutex);

	/* validate extent length */
	if (xlen > MAXXLEN)
		xlen = MAXXLEN;

	/* get the page's starting extent offset */
	xoff = pno << sbi->l2nbperpage;

	/* check if an allocation hint was provided */
	if ((hint = addressXAD(xp))) {
		/* get the size of the extent described by the hint */
		nxlen = lengthXAD(xp);

		/* check if the hint is for the portion of the file
		 * immediately previous to the current allocation
		 * request and if hint extent has the same abnr
		 * value as the current request.  if so, we can
		 * extend the hint extent to include the current
		 * extent if we can allocate the blocks immediately
		 * following the hint extent.
		 */
		if (offsetXAD(xp) + nxlen == xoff &&
		    abnr == ((xp->flag & XAD_NOTRECORDED) ? true : false))
			xaddr = hint + nxlen;

		/* adjust the hint to the last block of the extent */
		hint += (nxlen - 1);
	}

	/* allocate the disk blocks for the extent.  initially, extBalloc()
	 * will try to allocate disk blocks for the requested size (xlen).
	 * if this fails (xlen contiguous free blocks not avaliable), it'll
	 * try to allocate a smaller number of blocks (producing a smaller
	 * extent), with this smaller number of blocks consisting of the
	 * requested number of blocks rounded down to the next smaller
	 * power of 2 number (i.e. 16 -> 8).  it'll continue to round down
	 * and retry the allocation until the number of blocks to allocate
	 * is smaller than the number of blocks per page.
	 */
	nxlen = xlen;
	if ((rc = extBalloc(ip, hint ? hint : INOHINT(ip), &nxlen, &nxaddr))) {
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
		return (rc);
	}

	/* Allocate blocks to quota. */
	if (vfs_dq_alloc_block(ip, nxlen)) {
		dbFree(ip, nxaddr, (s64) nxlen);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
		return -EDQUOT;
	}

	/* determine the value of the extent flag */
	xflag = abnr ? XAD_NOTRECORDED : 0;

	/* if we can extend the hint extent to cover the current request,
	 * extend it.  otherwise, insert a new extent to
	 * cover the current request.
	 */
	if (xaddr && xaddr == nxaddr)
		rc = xtExtend(0, ip, xoff, (int) nxlen, 0);
	else
		rc = xtInsert(0, ip, xflag, xoff, (int) nxlen, &nxaddr, 0);

	/* if the extend or insert failed,
	 * free the newly allocated blocks and return the error.
	 */
	if (rc) {
		dbFree(ip, nxaddr, nxlen);
		vfs_dq_free_block(ip, nxlen);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
		return (rc);
	}

	/* set the results of the extent allocation */
	XADaddress(xp, nxaddr);
	XADlength(xp, nxlen);
	XADoffset(xp, xoff);
	xp->flag = xflag;

	mark_inode_dirty(ip);

	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	/*
	 * COMMIT_SyncList flags an anonymous tlock on page that is on
	 * sync list.
	 * We need to commit the inode to get the page written disk.
	 */
	if (test_and_clear_cflag(COMMIT_Synclist,ip))
		jfs_commit_inode(ip, 0);

	return (0);
}