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
struct inomap {int im_freeiag; int /*<<< orphan*/  im_ipimap; TYPE_1__* im_agctl; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct iag {int* extsmap; scalar_t__ nfreeexts; scalar_t__ iagfree; int /*<<< orphan*/  agstart; } ;
struct TYPE_2__ {int extfree; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGTOBLK (int,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int EXTSPERIAG ; 
 int EXTSPERSUM ; 
 int /*<<< orphan*/  IAGFREE_LOCK (struct inomap*) ; 
 int /*<<< orphan*/  IAGFREE_UNLOCK (struct inomap*) ; 
 int /*<<< orphan*/  IREAD_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IREAD_UNLOCK (int /*<<< orphan*/ ) ; 
 int L2EXTSPERSUM ; 
 int L2INOSPEREXT ; 
 int /*<<< orphan*/  RDWRLOCK_IMAP ; 
 int SMAPSZ ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int diFindFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int diIAGRead (struct inomap*,int,struct metapage**) ; 
 int /*<<< orphan*/  diInitInode (struct inode*,int,int,int,struct iag*) ; 
 int diNewExt (struct inomap*,struct iag*,int) ; 
 int diNewIAG (struct inomap*,int*,int,struct metapage**) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  le32_to_cpu (int) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  write_metapage (struct metapage*) ; 

__attribute__((used)) static int diAllocExt(struct inomap * imap, int agno, struct inode *ip)
{
	int rem, iagno, sword, extno, rc;
	struct metapage *mp;
	struct iag *iagp;

	/* check if the ag has any iags with free extents.  if not,
	 * allocate a new iag for the ag.
	 */
	if ((iagno = imap->im_agctl[agno].extfree) < 0) {
		/* If successful, diNewIAG will obtain the read lock on the
		 * imap inode.
		 */
		if ((rc = diNewIAG(imap, &iagno, agno, &mp))) {
			return (rc);
		}
		iagp = (struct iag *) mp->data;

		/* set the ag number if this a brand new iag
		 */
		iagp->agstart =
		    cpu_to_le64(AGTOBLK(agno, imap->im_ipimap));
	} else {
		/* read the iag.
		 */
		IREAD_LOCK(imap->im_ipimap, RDWRLOCK_IMAP);
		if ((rc = diIAGRead(imap, iagno, &mp))) {
			IREAD_UNLOCK(imap->im_ipimap);
			jfs_error(ip->i_sb, "diAllocExt: error reading iag");
			return rc;
		}
		iagp = (struct iag *) mp->data;
	}

	/* using the free extent summary map, find a free extent.
	 */
	for (sword = 0;; sword++) {
		if (sword >= SMAPSZ) {
			release_metapage(mp);
			IREAD_UNLOCK(imap->im_ipimap);
			jfs_error(ip->i_sb,
				  "diAllocExt: free ext summary map not found");
			return -EIO;
		}
		if (~iagp->extsmap[sword])
			break;
	}

	/* determine the extent number of the free extent.
	 */
	rem = diFindFree(le32_to_cpu(iagp->extsmap[sword]), 0);
	if (rem >= EXTSPERSUM) {
		release_metapage(mp);
		IREAD_UNLOCK(imap->im_ipimap);
		jfs_error(ip->i_sb, "diAllocExt: free extent not found");
		return -EIO;
	}
	extno = (sword << L2EXTSPERSUM) + rem;

	/* initialize the new extent.
	 */
	rc = diNewExt(imap, iagp, extno);
	IREAD_UNLOCK(imap->im_ipimap);
	if (rc) {
		/* something bad happened.  if a new iag was allocated,
		 * place it back on the inode map's iag free list, and
		 * clear the ag number information.
		 */
		if (iagp->nfreeexts == cpu_to_le32(EXTSPERIAG)) {
			IAGFREE_LOCK(imap);
			iagp->iagfree = cpu_to_le32(imap->im_freeiag);
			imap->im_freeiag = iagno;
			IAGFREE_UNLOCK(imap);
		}
		write_metapage(mp);
		return (rc);
	}

	/* set the results of the allocation and write the iag.
	 */
	diInitInode(ip, iagno, extno << L2INOSPEREXT, extno, iagp);

	write_metapage(mp);

	return (0);
}