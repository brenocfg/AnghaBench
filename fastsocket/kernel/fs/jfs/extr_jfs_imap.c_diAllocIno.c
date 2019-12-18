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
struct metapage {scalar_t__ data; } ;
struct inomap {int /*<<< orphan*/  im_ipimap; TYPE_1__* im_agctl; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct iag {int* inosmap; int* wmap; int /*<<< orphan*/  nfreeinos; } ;
struct TYPE_2__ {int inofree; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSPC ; 
 int EXTSPERSUM ; 
 int INOSPEREXT ; 
 int /*<<< orphan*/  IREAD_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IREAD_UNLOCK (int /*<<< orphan*/ ) ; 
 int L2EXTSPERSUM ; 
 int L2INOSPEREXT ; 
 int /*<<< orphan*/  RDWRLOCK_IMAP ; 
 int SMAPSZ ; 
 int diAllocBit (struct inomap*,struct iag*,int) ; 
 int diFindFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int diIAGRead (struct inomap*,int,struct metapage**) ; 
 int /*<<< orphan*/  diInitInode (struct inode*,int,int,int,struct iag*) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  le32_to_cpu (int) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  write_metapage (struct metapage*) ; 

__attribute__((used)) static int diAllocIno(struct inomap * imap, int agno, struct inode *ip)
{
	int iagno, ino, rc, rem, extno, sword;
	struct metapage *mp;
	struct iag *iagp;

	/* check if there are iags on the ag's free inode list.
	 */
	if ((iagno = imap->im_agctl[agno].inofree) < 0)
		return -ENOSPC;

	/* obtain read lock on imap inode */
	IREAD_LOCK(imap->im_ipimap, RDWRLOCK_IMAP);

	/* read the iag at the head of the list.
	 */
	if ((rc = diIAGRead(imap, iagno, &mp))) {
		IREAD_UNLOCK(imap->im_ipimap);
		return (rc);
	}
	iagp = (struct iag *) mp->data;

	/* better be free inodes in this iag if it is on the
	 * list.
	 */
	if (!iagp->nfreeinos) {
		IREAD_UNLOCK(imap->im_ipimap);
		release_metapage(mp);
		jfs_error(ip->i_sb,
			  "diAllocIno: nfreeinos = 0, but iag on freelist");
		return -EIO;
	}

	/* scan the free inode summary map to find an extent
	 * with free inodes.
	 */
	for (sword = 0;; sword++) {
		if (sword >= SMAPSZ) {
			IREAD_UNLOCK(imap->im_ipimap);
			release_metapage(mp);
			jfs_error(ip->i_sb,
				  "diAllocIno: free inode not found in summary map");
			return -EIO;
		}

		if (~iagp->inosmap[sword])
			break;
	}

	/* found a extent with free inodes. determine
	 * the extent number.
	 */
	rem = diFindFree(le32_to_cpu(iagp->inosmap[sword]), 0);
	if (rem >= EXTSPERSUM) {
		IREAD_UNLOCK(imap->im_ipimap);
		release_metapage(mp);
		jfs_error(ip->i_sb, "diAllocIno: no free extent found");
		return -EIO;
	}
	extno = (sword << L2EXTSPERSUM) + rem;

	/* find the first free inode in the extent.
	 */
	rem = diFindFree(le32_to_cpu(iagp->wmap[extno]), 0);
	if (rem >= INOSPEREXT) {
		IREAD_UNLOCK(imap->im_ipimap);
		release_metapage(mp);
		jfs_error(ip->i_sb, "diAllocIno: free inode not found");
		return -EIO;
	}

	/* compute the inode number within the iag.
	 */
	ino = (extno << L2INOSPEREXT) + rem;

	/* allocate the inode.
	 */
	rc = diAllocBit(imap, iagp, ino);
	IREAD_UNLOCK(imap->im_ipimap);
	if (rc) {
		release_metapage(mp);
		return (rc);
	}

	/* set the results of the allocation and write the iag.
	 */
	diInitInode(ip, iagno, ino, extno, iagp);
	write_metapage(mp);

	return (0);
}