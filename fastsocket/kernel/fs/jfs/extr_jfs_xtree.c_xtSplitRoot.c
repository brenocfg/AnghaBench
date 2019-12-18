#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flag; void* nextindex; void* maxentry; scalar_t__ prev; scalar_t__ next; int /*<<< orphan*/  self; } ;
struct metapage {TYPE_1__ header; int /*<<< orphan*/  i_sb; int /*<<< orphan*/ * xad; scalar_t__ data; } ;
typedef  struct metapage xtpage_t ;
typedef  int /*<<< orphan*/  xad_t ;
typedef  int /*<<< orphan*/  tid_t ;
struct xtsplit {int index; struct metapage* mp; int /*<<< orphan*/  addr; int /*<<< orphan*/  len; int /*<<< orphan*/  off; int /*<<< orphan*/  flag; struct pxdlist* pxdlist; } ;
struct TYPE_7__ {size_t offset; size_t length; } ;
struct xtlock {TYPE_2__ lwm; } ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct pxdlist {size_t npxd; int /*<<< orphan*/ * pxd; } ;
struct inode {TYPE_1__ header; int /*<<< orphan*/  i_sb; int /*<<< orphan*/ * xad; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  pxd_t ;
struct TYPE_10__ {struct metapage i_xtroot; } ;
struct TYPE_9__ {int /*<<< orphan*/  nbperpage; } ;
struct TYPE_8__ {int /*<<< orphan*/  split; } ;

/* Variables and functions */
 int BT_INTERNAL ; 
 int BT_LEAF ; 
 int /*<<< orphan*/  BT_MARK_DIRTY (struct metapage*,struct metapage*) ; 
 int /*<<< orphan*/  COMMIT_Nolink ; 
 int EDQUOT ; 
 int EIO ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 TYPE_5__* JFS_IP (struct metapage*) ; 
 TYPE_4__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int L2XTSLOTSIZE ; 
 int PSIZE ; 
 int /*<<< orphan*/  XAD_NEW ; 
 size_t XTENTRYSTART ; 
 int /*<<< orphan*/  XT_PUTENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addressPXD (int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (size_t) ; 
 struct metapage* get_metapage (struct metapage*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  jfs_info (char*,struct metapage*,struct metapage*) ; 
 size_t le16_to_cpu (void*) ; 
 int /*<<< orphan*/  lengthPXD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  test_cflag (int /*<<< orphan*/ ,struct metapage*) ; 
 int tlckGROW ; 
 int tlckNEW ; 
 int tlckXTREE ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct metapage*,struct metapage*,int) ; 
 scalar_t__ vfs_dq_alloc_block (struct metapage*,int /*<<< orphan*/ ) ; 
 TYPE_3__ xtStat ; 

__attribute__((used)) static int
xtSplitRoot(tid_t tid,
	    struct inode *ip, struct xtsplit * split, struct metapage ** rmpp)
{
	xtpage_t *sp;
	struct metapage *rmp;
	xtpage_t *rp;
	s64 rbn;
	int skip, nextindex;
	xad_t *xad;
	pxd_t *pxd;
	struct pxdlist *pxdlist;
	struct tlock *tlck;
	struct xtlock *xtlck;

	sp = &JFS_IP(ip)->i_xtroot;

	INCREMENT(xtStat.split);

	/*
	 *	allocate a single (right) child page
	 */
	pxdlist = split->pxdlist;
	pxd = &pxdlist->pxd[pxdlist->npxd];
	pxdlist->npxd++;
	rbn = addressPXD(pxd);
	rmp = get_metapage(ip, rbn, PSIZE, 1);
	if (rmp == NULL)
		return -EIO;

	/* Allocate blocks to quota. */
	if (vfs_dq_alloc_block(ip, lengthPXD(pxd))) {
		release_metapage(rmp);
		return -EDQUOT;
	}

	jfs_info("xtSplitRoot: ip:0x%p rmp:0x%p", ip, rmp);

	/*
	 * acquire a transaction lock on the new right page;
	 *
	 * action: new page;
	 */
	BT_MARK_DIRTY(rmp, ip);

	rp = (xtpage_t *) rmp->data;
	rp->header.flag =
	    (sp->header.flag & BT_LEAF) ? BT_LEAF : BT_INTERNAL;
	rp->header.self = *pxd;
	rp->header.nextindex = cpu_to_le16(XTENTRYSTART);
	rp->header.maxentry = cpu_to_le16(PSIZE >> L2XTSLOTSIZE);

	/* initialize sibling pointers */
	rp->header.next = 0;
	rp->header.prev = 0;

	/*
	 * copy the in-line root page into new right page extent
	 */
	nextindex = le16_to_cpu(sp->header.maxentry);
	memmove(&rp->xad[XTENTRYSTART], &sp->xad[XTENTRYSTART],
		(nextindex - XTENTRYSTART) << L2XTSLOTSIZE);

	/*
	 * insert the new entry into the new right/child page
	 * (skip index in the new right page will not change)
	 */
	skip = split->index;
	/* if insert into middle, shift right remaining entries */
	if (skip != nextindex)
		memmove(&rp->xad[skip + 1], &rp->xad[skip],
			(nextindex - skip) * sizeof(xad_t));

	xad = &rp->xad[skip];
	XT_PUTENTRY(xad, split->flag, split->off, split->len, split->addr);

	/* update page header */
	rp->header.nextindex = cpu_to_le16(nextindex + 1);

	if (!test_cflag(COMMIT_Nolink, ip)) {
		tlck = txLock(tid, ip, rmp, tlckXTREE | tlckNEW);
		xtlck = (struct xtlock *) & tlck->lock;
		xtlck->lwm.offset = XTENTRYSTART;
		xtlck->lwm.length = le16_to_cpu(rp->header.nextindex) -
		    XTENTRYSTART;
	}

	/*
	 *	reset the root
	 *
	 * init root with the single entry for the new right page
	 * set the 1st entry offset to 0, which force the left-most key
	 * at any level of the tree to be less than any search key.
	 */
	/*
	 * acquire a transaction lock on the root page (in-memory inode);
	 *
	 * action: root split;
	 */
	BT_MARK_DIRTY(split->mp, ip);

	xad = &sp->xad[XTENTRYSTART];
	XT_PUTENTRY(xad, XAD_NEW, 0, JFS_SBI(ip->i_sb)->nbperpage, rbn);

	/* update page header of root */
	sp->header.flag &= ~BT_LEAF;
	sp->header.flag |= BT_INTERNAL;

	sp->header.nextindex = cpu_to_le16(XTENTRYSTART + 1);

	if (!test_cflag(COMMIT_Nolink, ip)) {
		tlck = txLock(tid, ip, split->mp, tlckXTREE | tlckGROW);
		xtlck = (struct xtlock *) & tlck->lock;
		xtlck->lwm.offset = XTENTRYSTART;
		xtlck->lwm.length = 1;
	}

	*rmpp = rmp;

	jfs_info("xtSplitRoot: sp:0x%p rp:0x%p", sp, rp);
	return 0;
}