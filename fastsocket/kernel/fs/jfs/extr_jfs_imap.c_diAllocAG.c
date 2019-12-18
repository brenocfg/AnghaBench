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
struct inomap {TYPE_1__* im_agctl; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int numfree; int numinos; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSPC ; 
 int diAllocExt (struct inomap*,int,struct inode*) ; 
 int diAllocIno (struct inomap*,int,struct inode*) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
diAllocAG(struct inomap * imap, int agno, bool dir, struct inode *ip)
{
	int rc, addext, numfree, numinos;

	/* get the number of free and the number of backed disk
	 * inodes currently within the ag.
	 */
	numfree = imap->im_agctl[agno].numfree;
	numinos = imap->im_agctl[agno].numinos;

	if (numfree > numinos) {
		jfs_error(ip->i_sb, "diAllocAG: numfree > numinos");
		return -EIO;
	}

	/* determine if we should allocate a new extent of free inodes
	 * within the ag: for directory inodes, add a new extent
	 * if there are a small number of free inodes or number of free
	 * inodes is a small percentage of the number of backed inodes.
	 */
	if (dir)
		addext = (numfree < 64 ||
			  (numfree < 256
			   && ((numfree * 100) / numinos) <= 20));
	else
		addext = (numfree == 0);

	/*
	 * try to allocate a new extent of free inodes.
	 */
	if (addext) {
		/* if free space is not avaliable for this new extent, try
		 * below to allocate a free and existing (already backed)
		 * inode from the ag.
		 */
		if ((rc = diAllocExt(imap, agno, ip)) != -ENOSPC)
			return (rc);
	}

	/*
	 * try to allocate an existing free inode from the ag.
	 */
	return (diAllocIno(imap, agno, ip));
}