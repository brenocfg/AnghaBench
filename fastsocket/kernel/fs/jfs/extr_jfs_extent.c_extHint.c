#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flag; } ;
typedef  TYPE_1__ xad_t ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
typedef  int s64 ;
struct TYPE_8__ {int nbperpage; int l2bsize; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_6__* JFS_SBI (struct super_block*) ; 
 int POFFSET ; 
 int XAD_NOTRECORDED ; 
 int /*<<< orphan*/  XADaddress (TYPE_1__*,int) ; 
 int /*<<< orphan*/  XADlength (TYPE_1__*,int) ; 
 int /*<<< orphan*/  XADoffset (TYPE_1__*,int) ; 
 int /*<<< orphan*/  jfs_error (struct super_block*,char*) ; 
 int xtLookup (struct inode*,int,int,int*,int*,int*,int /*<<< orphan*/ ) ; 

int extHint(struct inode *ip, s64 offset, xad_t * xp)
{
	struct super_block *sb = ip->i_sb;
	int nbperpage = JFS_SBI(sb)->nbperpage;
	s64 prev;
	int rc = 0;
	s64 xaddr;
	int xlen;
	int xflag;

	/* init the hint as "no hint provided" */
	XADaddress(xp, 0);

	/* determine the starting extent offset of the page previous
	 * to the page containing the offset.
	 */
	prev = ((offset & ~POFFSET) >> JFS_SBI(sb)->l2bsize) - nbperpage;

	/* if the offset is in the first page of the file, no hint provided.
	 */
	if (prev < 0)
		goto out;

	rc = xtLookup(ip, prev, nbperpage, &xflag, &xaddr, &xlen, 0);

	if ((rc == 0) && xlen) {
		if (xlen != nbperpage) {
			jfs_error(ip->i_sb, "extHint: corrupt xtree");
			rc = -EIO;
		}
		XADaddress(xp, xaddr);
		XADlength(xp, xlen);
		XADoffset(xp, prev);
		/*
		 * only preserve the abnr flag within the xad flags
		 * of the returned hint.
		 */
		xp->flag  = xflag & XAD_NOTRECORDED;
	} else
		rc = 0;

out:
	return (rc);
}