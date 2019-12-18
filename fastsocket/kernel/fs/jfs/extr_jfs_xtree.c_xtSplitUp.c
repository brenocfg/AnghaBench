#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flag; int /*<<< orphan*/  nextindex; int /*<<< orphan*/  maxentry; } ;
struct TYPE_10__ {TYPE_2__ header; int /*<<< orphan*/ * xad; } ;
typedef  TYPE_3__ xtpage_t ;
typedef  int /*<<< orphan*/  xad_t ;
typedef  int /*<<< orphan*/  tid_t ;
struct xtsplit {int index; int len; int /*<<< orphan*/  addr; int /*<<< orphan*/  off; int /*<<< orphan*/  flag; struct metapage* mp; struct pxdlist* pxdlist; } ;
struct TYPE_8__ {int offset; int length; } ;
struct xtlock {TYPE_1__ lwm; } ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct pxdlist {scalar_t__ maxnpxd; int /*<<< orphan*/ * pxd; scalar_t__ npxd; } ;
struct metapage {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct btstack {int nsplit; } ;
struct btframe {int index; int /*<<< orphan*/  bn; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  pxd_t ;
struct TYPE_12__ {int mode2; } ;
struct TYPE_11__ {int nbperpage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MARK_DIRTY (struct metapage*,struct inode*) ; 
 struct btframe* BT_POP (struct btstack*) ; 
 int BT_ROOT ; 
 int /*<<< orphan*/  COMMIT_Nolink ; 
 int EIO ; 
 int INLINEEA ; 
 TYPE_7__* JFS_IP (struct inode*) ; 
 TYPE_6__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int L2XTSLOTSIZE ; 
 int /*<<< orphan*/  PSIZE ; 
 int /*<<< orphan*/  PXDaddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PXDlength (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XAD_NEW ; 
 size_t XTENTRYSTART ; 
 int XTROOTMAXSLOT ; 
 int /*<<< orphan*/  XT_GETPAGE (struct inode*,int /*<<< orphan*/ ,struct metapage*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 TYPE_3__* XT_PAGE (struct inode*,struct metapage*) ; 
 int /*<<< orphan*/  XT_PUTENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XT_PUTPAGE (struct metapage*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int dbAlloc (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  offsetXAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int tlckGROW ; 
 int tlckXTREE ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 
 int xtSplitPage (int /*<<< orphan*/ ,struct inode*,struct xtsplit*,struct metapage**,int /*<<< orphan*/ *) ; 
 int xtSplitRoot (int /*<<< orphan*/ ,struct inode*,struct xtsplit*,struct metapage**) ; 

__attribute__((used)) static int
xtSplitUp(tid_t tid,
	  struct inode *ip, struct xtsplit * split, struct btstack * btstack)
{
	int rc = 0;
	struct metapage *smp;
	xtpage_t *sp;		/* split page */
	struct metapage *rmp;
	s64 rbn;		/* new right page block number */
	struct metapage *rcmp;
	xtpage_t *rcp;		/* right child page */
	s64 rcbn;		/* right child page block number */
	int skip;		/* index of entry of insertion */
	int nextindex;		/* next available entry index of p */
	struct btframe *parent;	/* parent page entry on traverse stack */
	xad_t *xad;
	s64 xaddr;
	int xlen;
	int nsplit;		/* number of pages split */
	struct pxdlist pxdlist;
	pxd_t *pxd;
	struct tlock *tlck;
	struct xtlock *xtlck;

	smp = split->mp;
	sp = XT_PAGE(ip, smp);

	/* is inode xtree root extension/inline EA area free ? */
	if ((sp->header.flag & BT_ROOT) && (!S_ISDIR(ip->i_mode)) &&
	    (le16_to_cpu(sp->header.maxentry) < XTROOTMAXSLOT) &&
	    (JFS_IP(ip)->mode2 & INLINEEA)) {
		sp->header.maxentry = cpu_to_le16(XTROOTMAXSLOT);
		JFS_IP(ip)->mode2 &= ~INLINEEA;

		BT_MARK_DIRTY(smp, ip);
		/*
		 * acquire a transaction lock on the leaf page;
		 *
		 * action: xad insertion/extension;
		 */

		/* if insert into middle, shift right remaining entries. */
		skip = split->index;
		nextindex = le16_to_cpu(sp->header.nextindex);
		if (skip < nextindex)
			memmove(&sp->xad[skip + 1], &sp->xad[skip],
				(nextindex - skip) * sizeof(xad_t));

		/* insert the new entry: mark the entry NEW */
		xad = &sp->xad[skip];
		XT_PUTENTRY(xad, split->flag, split->off, split->len,
			    split->addr);

		/* advance next available entry index */
		le16_add_cpu(&sp->header.nextindex, 1);

		/* Don't log it if there are no links to the file */
		if (!test_cflag(COMMIT_Nolink, ip)) {
			tlck = txLock(tid, ip, smp, tlckXTREE | tlckGROW);
			xtlck = (struct xtlock *) & tlck->lock;
			xtlck->lwm.offset = (xtlck->lwm.offset) ?
			    min(skip, (int)xtlck->lwm.offset) : skip;
			xtlck->lwm.length =
			    le16_to_cpu(sp->header.nextindex) -
			    xtlck->lwm.offset;
		}

		return 0;
	}

	/*
	 * allocate new index blocks to cover index page split(s)
	 *
	 * allocation hint: ?
	 */
	if (split->pxdlist == NULL) {
		nsplit = btstack->nsplit;
		split->pxdlist = &pxdlist;
		pxdlist.maxnpxd = pxdlist.npxd = 0;
		pxd = &pxdlist.pxd[0];
		xlen = JFS_SBI(ip->i_sb)->nbperpage;
		for (; nsplit > 0; nsplit--, pxd++) {
			if ((rc = dbAlloc(ip, (s64) 0, (s64) xlen, &xaddr))
			    == 0) {
				PXDaddress(pxd, xaddr);
				PXDlength(pxd, xlen);

				pxdlist.maxnpxd++;

				continue;
			}

			/* undo allocation */

			XT_PUTPAGE(smp);
			return rc;
		}
	}

	/*
	 * Split leaf page <sp> into <sp> and a new right page <rp>.
	 *
	 * The split routines insert the new entry into the leaf page,
	 * and acquire txLock as appropriate.
	 * return <rp> pinned and its block number <rpbn>.
	 */
	rc = (sp->header.flag & BT_ROOT) ?
	    xtSplitRoot(tid, ip, split, &rmp) :
	    xtSplitPage(tid, ip, split, &rmp, &rbn);

	XT_PUTPAGE(smp);

	if (rc)
		return -EIO;
	/*
	 * propagate up the router entry for the leaf page just split
	 *
	 * insert a router entry for the new page into the parent page,
	 * propagate the insert/split up the tree by walking back the stack
	 * of (bn of parent page, index of child page entry in parent page)
	 * that were traversed during the search for the page that split.
	 *
	 * the propagation of insert/split up the tree stops if the root
	 * splits or the page inserted into doesn't have to split to hold
	 * the new entry.
	 *
	 * the parent entry for the split page remains the same, and
	 * a new entry is inserted at its right with the first key and
	 * block number of the new right page.
	 *
	 * There are a maximum of 3 pages pinned at any time:
	 * right child, left parent and right parent (when the parent splits)
	 * to keep the child page pinned while working on the parent.
	 * make sure that all pins are released at exit.
	 */
	while ((parent = BT_POP(btstack)) != NULL) {
		/* parent page specified by stack frame <parent> */

		/* keep current child pages <rcp> pinned */
		rcmp = rmp;
		rcbn = rbn;
		rcp = XT_PAGE(ip, rcmp);

		/*
		 * insert router entry in parent for new right child page <rp>
		 */
		/* get/pin the parent page <sp> */
		XT_GETPAGE(ip, parent->bn, smp, PSIZE, sp, rc);
		if (rc) {
			XT_PUTPAGE(rcmp);
			return rc;
		}

		/*
		 * The new key entry goes ONE AFTER the index of parent entry,
		 * because the split was to the right.
		 */
		skip = parent->index + 1;

		/*
		 * split or shift right remaining entries of the parent page
		 */
		nextindex = le16_to_cpu(sp->header.nextindex);
		/*
		 * parent page is full - split the parent page
		 */
		if (nextindex == le16_to_cpu(sp->header.maxentry)) {
			/* init for parent page split */
			split->mp = smp;
			split->index = skip;	/* index at insert */
			split->flag = XAD_NEW;
			split->off = offsetXAD(&rcp->xad[XTENTRYSTART]);
			split->len = JFS_SBI(ip->i_sb)->nbperpage;
			split->addr = rcbn;

			/* unpin previous right child page */
			XT_PUTPAGE(rcmp);

			/* The split routines insert the new entry,
			 * and acquire txLock as appropriate.
			 * return <rp> pinned and its block number <rpbn>.
			 */
			rc = (sp->header.flag & BT_ROOT) ?
			    xtSplitRoot(tid, ip, split, &rmp) :
			    xtSplitPage(tid, ip, split, &rmp, &rbn);
			if (rc) {
				XT_PUTPAGE(smp);
				return rc;
			}

			XT_PUTPAGE(smp);
			/* keep new child page <rp> pinned */
		}
		/*
		 * parent page is not full - insert in parent page
		 */
		else {
			/*
			 * insert router entry in parent for the right child
			 * page from the first entry of the right child page:
			 */
			/*
			 * acquire a transaction lock on the parent page;
			 *
			 * action: router xad insertion;
			 */
			BT_MARK_DIRTY(smp, ip);

			/*
			 * if insert into middle, shift right remaining entries
			 */
			if (skip < nextindex)
				memmove(&sp->xad[skip + 1], &sp->xad[skip],
					(nextindex -
					 skip) << L2XTSLOTSIZE);

			/* insert the router entry */
			xad = &sp->xad[skip];
			XT_PUTENTRY(xad, XAD_NEW,
				    offsetXAD(&rcp->xad[XTENTRYSTART]),
				    JFS_SBI(ip->i_sb)->nbperpage, rcbn);

			/* advance next available entry index. */
			le16_add_cpu(&sp->header.nextindex, 1);

			/* Don't log it if there are no links to the file */
			if (!test_cflag(COMMIT_Nolink, ip)) {
				tlck = txLock(tid, ip, smp,
					      tlckXTREE | tlckGROW);
				xtlck = (struct xtlock *) & tlck->lock;
				xtlck->lwm.offset = (xtlck->lwm.offset) ?
				    min(skip, (int)xtlck->lwm.offset) : skip;
				xtlck->lwm.length =
				    le16_to_cpu(sp->header.nextindex) -
				    xtlck->lwm.offset;
			}

			/* unpin parent page */
			XT_PUTPAGE(smp);

			/* exit propagate up */
			break;
		}
	}

	/* unpin current right page */
	XT_PUTPAGE(rmp);

	return 0;
}