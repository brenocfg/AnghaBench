#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flag; void* nextindex; void* maxentry; void* prev; void* next; int /*<<< orphan*/  self; } ;
struct TYPE_10__ {TYPE_2__ header; int /*<<< orphan*/ * xad; } ;
typedef  TYPE_3__ xtpage_t ;
typedef  int /*<<< orphan*/  xad_t ;
typedef  int /*<<< orphan*/  tid_t ;
struct xtsplit {int index; int /*<<< orphan*/  addr; int /*<<< orphan*/  len; int /*<<< orphan*/  off; int /*<<< orphan*/  flag; struct pxdlist* pxdlist; struct metapage* mp; } ;
struct TYPE_8__ {size_t offset; int length; } ;
struct xtlock {TYPE_1__ lwm; } ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct pxdlist {size_t npxd; int /*<<< orphan*/ * pxd; } ;
struct metapage {scalar_t__ data; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  pxd_t ;
struct TYPE_11__ {int /*<<< orphan*/  split; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MARK_DIRTY (struct metapage*,struct inode*) ; 
 int BT_TYPE ; 
 int /*<<< orphan*/  COMMIT_Nolink ; 
 int EDQUOT ; 
 int EIO ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 int L2XTSLOTSIZE ; 
 int /*<<< orphan*/  PSIZE ; 
 size_t XTENTRYSTART ; 
 int /*<<< orphan*/  XT_GETPAGE (struct inode*,scalar_t__,struct metapage*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 TYPE_3__* XT_PAGE (struct inode*,struct metapage*) ; 
 int /*<<< orphan*/  XT_PUTENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XT_PUTPAGE (struct metapage*) ; 
 scalar_t__ addressPXD (int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (size_t) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 struct metapage* get_metapage (struct inode*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jfs_info (char*,TYPE_3__*,...) ; 
 size_t le16_to_cpu (void*) ; 
 scalar_t__ le64_to_cpu (void*) ; 
 scalar_t__ lengthPXD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int tlckGROW ; 
 int tlckNEW ; 
 int tlckRELINK ; 
 int tlckXTREE ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 
 scalar_t__ vfs_dq_alloc_block (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  vfs_dq_free_block (struct inode*,int) ; 
 TYPE_4__ xtStat ; 

__attribute__((used)) static int
xtSplitPage(tid_t tid, struct inode *ip,
	    struct xtsplit * split, struct metapage ** rmpp, s64 * rbnp)
{
	int rc = 0;
	struct metapage *smp;
	xtpage_t *sp;
	struct metapage *rmp;
	xtpage_t *rp;		/* new right page allocated */
	s64 rbn;		/* new right page block number */
	struct metapage *mp;
	xtpage_t *p;
	s64 nextbn;
	int skip, maxentry, middle, righthalf, n;
	xad_t *xad;
	struct pxdlist *pxdlist;
	pxd_t *pxd;
	struct tlock *tlck;
	struct xtlock *sxtlck = NULL, *rxtlck = NULL;
	int quota_allocation = 0;

	smp = split->mp;
	sp = XT_PAGE(ip, smp);

	INCREMENT(xtStat.split);

	pxdlist = split->pxdlist;
	pxd = &pxdlist->pxd[pxdlist->npxd];
	pxdlist->npxd++;
	rbn = addressPXD(pxd);

	/* Allocate blocks to quota. */
	if (vfs_dq_alloc_block(ip, lengthPXD(pxd))) {
		rc = -EDQUOT;
		goto clean_up;
	}

	quota_allocation += lengthPXD(pxd);

	/*
	 * allocate the new right page for the split
	 */
	rmp = get_metapage(ip, rbn, PSIZE, 1);
	if (rmp == NULL) {
		rc = -EIO;
		goto clean_up;
	}

	jfs_info("xtSplitPage: ip:0x%p smp:0x%p rmp:0x%p", ip, smp, rmp);

	BT_MARK_DIRTY(rmp, ip);
	/*
	 * action: new page;
	 */

	rp = (xtpage_t *) rmp->data;
	rp->header.self = *pxd;
	rp->header.flag = sp->header.flag & BT_TYPE;
	rp->header.maxentry = sp->header.maxentry;	/* little-endian */
	rp->header.nextindex = cpu_to_le16(XTENTRYSTART);

	BT_MARK_DIRTY(smp, ip);
	/* Don't log it if there are no links to the file */
	if (!test_cflag(COMMIT_Nolink, ip)) {
		/*
		 * acquire a transaction lock on the new right page;
		 */
		tlck = txLock(tid, ip, rmp, tlckXTREE | tlckNEW);
		rxtlck = (struct xtlock *) & tlck->lock;
		rxtlck->lwm.offset = XTENTRYSTART;
		/*
		 * acquire a transaction lock on the split page
		 */
		tlck = txLock(tid, ip, smp, tlckXTREE | tlckGROW);
		sxtlck = (struct xtlock *) & tlck->lock;
	}

	/*
	 * initialize/update sibling pointers of <sp> and <rp>
	 */
	nextbn = le64_to_cpu(sp->header.next);
	rp->header.next = cpu_to_le64(nextbn);
	rp->header.prev = cpu_to_le64(addressPXD(&sp->header.self));
	sp->header.next = cpu_to_le64(rbn);

	skip = split->index;

	/*
	 *	sequential append at tail (after last entry of last page)
	 *
	 * if splitting the last page on a level because of appending
	 * a entry to it (skip is maxentry), it's likely that the access is
	 * sequential. adding an empty page on the side of the level is less
	 * work and can push the fill factor much higher than normal.
	 * if we're wrong it's no big deal -  we will do the split the right
	 * way next time.
	 * (it may look like it's equally easy to do a similar hack for
	 * reverse sorted data, that is, split the tree left, but it's not.
	 * Be my guest.)
	 */
	if (nextbn == 0 && skip == le16_to_cpu(sp->header.maxentry)) {
		/*
		 * acquire a transaction lock on the new/right page;
		 *
		 * action: xad insertion;
		 */
		/* insert entry at the first entry of the new right page */
		xad = &rp->xad[XTENTRYSTART];
		XT_PUTENTRY(xad, split->flag, split->off, split->len,
			    split->addr);

		rp->header.nextindex = cpu_to_le16(XTENTRYSTART + 1);

		if (!test_cflag(COMMIT_Nolink, ip)) {
			/* rxtlck->lwm.offset = XTENTRYSTART; */
			rxtlck->lwm.length = 1;
		}

		*rmpp = rmp;
		*rbnp = rbn;

		jfs_info("xtSplitPage: sp:0x%p rp:0x%p", sp, rp);
		return 0;
	}

	/*
	 *	non-sequential insert (at possibly middle page)
	 */

	/*
	 * update previous pointer of old next/right page of <sp>
	 */
	if (nextbn != 0) {
		XT_GETPAGE(ip, nextbn, mp, PSIZE, p, rc);
		if (rc) {
			XT_PUTPAGE(rmp);
			goto clean_up;
		}

		BT_MARK_DIRTY(mp, ip);
		/*
		 * acquire a transaction lock on the next page;
		 *
		 * action:sibling pointer update;
		 */
		if (!test_cflag(COMMIT_Nolink, ip))
			tlck = txLock(tid, ip, mp, tlckXTREE | tlckRELINK);

		p->header.prev = cpu_to_le64(rbn);

		/* sibling page may have been updated previously, or
		 * it may be updated later;
		 */

		XT_PUTPAGE(mp);
	}

	/*
	 * split the data between the split and new/right pages
	 */
	maxentry = le16_to_cpu(sp->header.maxentry);
	middle = maxentry >> 1;
	righthalf = maxentry - middle;

	/*
	 * skip index in old split/left page - insert into left page:
	 */
	if (skip <= middle) {
		/* move right half of split page to the new right page */
		memmove(&rp->xad[XTENTRYSTART], &sp->xad[middle],
			righthalf << L2XTSLOTSIZE);

		/* shift right tail of left half to make room for new entry */
		if (skip < middle)
			memmove(&sp->xad[skip + 1], &sp->xad[skip],
				(middle - skip) << L2XTSLOTSIZE);

		/* insert new entry */
		xad = &sp->xad[skip];
		XT_PUTENTRY(xad, split->flag, split->off, split->len,
			    split->addr);

		/* update page header */
		sp->header.nextindex = cpu_to_le16(middle + 1);
		if (!test_cflag(COMMIT_Nolink, ip)) {
			sxtlck->lwm.offset = (sxtlck->lwm.offset) ?
			    min(skip, (int)sxtlck->lwm.offset) : skip;
		}

		rp->header.nextindex =
		    cpu_to_le16(XTENTRYSTART + righthalf);
	}
	/*
	 * skip index in new right page - insert into right page:
	 */
	else {
		/* move left head of right half to right page */
		n = skip - middle;
		memmove(&rp->xad[XTENTRYSTART], &sp->xad[middle],
			n << L2XTSLOTSIZE);

		/* insert new entry */
		n += XTENTRYSTART;
		xad = &rp->xad[n];
		XT_PUTENTRY(xad, split->flag, split->off, split->len,
			    split->addr);

		/* move right tail of right half to right page */
		if (skip < maxentry)
			memmove(&rp->xad[n + 1], &sp->xad[skip],
				(maxentry - skip) << L2XTSLOTSIZE);

		/* update page header */
		sp->header.nextindex = cpu_to_le16(middle);
		if (!test_cflag(COMMIT_Nolink, ip)) {
			sxtlck->lwm.offset = (sxtlck->lwm.offset) ?
			    min(middle, (int)sxtlck->lwm.offset) : middle;
		}

		rp->header.nextindex = cpu_to_le16(XTENTRYSTART +
						   righthalf + 1);
	}

	if (!test_cflag(COMMIT_Nolink, ip)) {
		sxtlck->lwm.length = le16_to_cpu(sp->header.nextindex) -
		    sxtlck->lwm.offset;

		/* rxtlck->lwm.offset = XTENTRYSTART; */
		rxtlck->lwm.length = le16_to_cpu(rp->header.nextindex) -
		    XTENTRYSTART;
	}

	*rmpp = rmp;
	*rbnp = rbn;

	jfs_info("xtSplitPage: sp:0x%p rp:0x%p", sp, rp);
	return rc;

      clean_up:

	/* Rollback quota allocation. */
	if (quota_allocation)
		vfs_dq_free_block(ip, quota_allocation);

	return (rc);
}