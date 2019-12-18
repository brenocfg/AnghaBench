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
typedef  int u32 ;
struct metapage {scalar_t__ data; } ;
struct jfs_sb_info {unsigned long l2nbperpage; int nbperpage; int l2niperblk; struct inode* ipimap; } ;
struct inomap {scalar_t__ im_nbperiext; } ;
struct inode {int i_ino; int /*<<< orphan*/  i_sb; } ;
struct iag {int /*<<< orphan*/  agstart; int /*<<< orphan*/ * inoext; } ;
struct dinode {int /*<<< orphan*/  di_nlink; int /*<<< orphan*/  di_number; } ;
typedef  unsigned long s64 ;
struct TYPE_2__ {int active_ag; int /*<<< orphan*/  agno; struct inomap* i_imap; struct inode* ipimap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTOAG (unsigned long,struct jfs_sb_info*) ; 
 int EIO ; 
 int ESTALE ; 
 unsigned long INOPBLK (int /*<<< orphan*/ *,int,unsigned long) ; 
 int INOSPERIAG ; 
 int INOSPERPAGE ; 
 int INOTOIAG (int) ; 
 int /*<<< orphan*/  IREAD_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IREAD_UNLOCK (struct inode*) ; 
 TYPE_1__* JFS_IP (struct inode*) ; 
 struct jfs_sb_info* JFS_SBI (int /*<<< orphan*/ ) ; 
 int L2INOSPEREXT ; 
 int /*<<< orphan*/  PSIZE ; 
 int /*<<< orphan*/  RDWRLOCK_IMAP ; 
 scalar_t__ addressPXD (int /*<<< orphan*/ *) ; 
 int copy_from_dinode (struct dinode*,struct inode*) ; 
 int diIAGRead (struct inomap*,int,struct metapage**) ; 
 int /*<<< orphan*/  jfs_err (char*,...) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jfs_info (char*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ lengthPXD (int /*<<< orphan*/ *) ; 
 struct metapage* read_metapage (struct inode*,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 

int diRead(struct inode *ip)
{
	struct jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	int iagno, ino, extno, rc;
	struct inode *ipimap;
	struct dinode *dp;
	struct iag *iagp;
	struct metapage *mp;
	s64 blkno, agstart;
	struct inomap *imap;
	int block_offset;
	int inodes_left;
	unsigned long pageno;
	int rel_inode;

	jfs_info("diRead: ino = %ld", ip->i_ino);

	ipimap = sbi->ipimap;
	JFS_IP(ip)->ipimap = ipimap;

	/* determine the iag number for this inode (number) */
	iagno = INOTOIAG(ip->i_ino);

	/* read the iag */
	imap = JFS_IP(ipimap)->i_imap;
	IREAD_LOCK(ipimap, RDWRLOCK_IMAP);
	rc = diIAGRead(imap, iagno, &mp);
	IREAD_UNLOCK(ipimap);
	if (rc) {
		jfs_err("diRead: diIAGRead returned %d", rc);
		return (rc);
	}

	iagp = (struct iag *) mp->data;

	/* determine inode extent that holds the disk inode */
	ino = ip->i_ino & (INOSPERIAG - 1);
	extno = ino >> L2INOSPEREXT;

	if ((lengthPXD(&iagp->inoext[extno]) != imap->im_nbperiext) ||
	    (addressPXD(&iagp->inoext[extno]) == 0)) {
		release_metapage(mp);
		return -ESTALE;
	}

	/* get disk block number of the page within the inode extent
	 * that holds the disk inode.
	 */
	blkno = INOPBLK(&iagp->inoext[extno], ino, sbi->l2nbperpage);

	/* get the ag for the iag */
	agstart = le64_to_cpu(iagp->agstart);

	release_metapage(mp);

	rel_inode = (ino & (INOSPERPAGE - 1));
	pageno = blkno >> sbi->l2nbperpage;

	if ((block_offset = ((u32) blkno & (sbi->nbperpage - 1)))) {
		/*
		 * OS/2 didn't always align inode extents on page boundaries
		 */
		inodes_left =
		     (sbi->nbperpage - block_offset) << sbi->l2niperblk;

		if (rel_inode < inodes_left)
			rel_inode += block_offset << sbi->l2niperblk;
		else {
			pageno += 1;
			rel_inode -= inodes_left;
		}
	}

	/* read the page of disk inode */
	mp = read_metapage(ipimap, pageno << sbi->l2nbperpage, PSIZE, 1);
	if (!mp) {
		jfs_err("diRead: read_metapage failed");
		return -EIO;
	}

	/* locate the disk inode requested */
	dp = (struct dinode *) mp->data;
	dp += rel_inode;

	if (ip->i_ino != le32_to_cpu(dp->di_number)) {
		jfs_error(ip->i_sb, "diRead: i_ino != di_number");
		rc = -EIO;
	} else if (le32_to_cpu(dp->di_nlink) == 0)
		rc = -ESTALE;
	else
		/* copy the disk inode to the in-memory inode */
		rc = copy_from_dinode(dp, ip);

	release_metapage(mp);

	/* set the ag for the inode */
	JFS_IP(ip)->agno = BLKTOAG(agstart, sbi);
	JFS_IP(ip)->active_ag = -1;

	return (rc);
}