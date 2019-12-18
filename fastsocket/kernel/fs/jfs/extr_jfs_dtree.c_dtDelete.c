#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  tid_t ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct metapage {int dummy; } ;
struct lv {int length; scalar_t__ offset; } ;
struct ldtentry {int /*<<< orphan*/  index; } ;
struct inode {int dummy; } ;
struct dt_lock {size_t index; size_t maxcnt; struct lv* lv; } ;
struct component_name {int dummy; } ;
struct btstack {int /*<<< orphan*/  top; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_8__ {int nextindex; int flag; scalar_t__ next; scalar_t__ stblindex; } ;
struct TYPE_9__ {int /*<<< orphan*/ * slot; TYPE_1__ header; } ;
typedef  TYPE_2__ dtpage_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MARK_DIRTY (struct metapage*,struct inode*) ; 
 int BT_ROOT ; 
 scalar_t__ DO_INDEX (struct inode*) ; 
 int /*<<< orphan*/  DT_GETPAGE (struct inode*,int /*<<< orphan*/ ,struct metapage*,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  DT_GETSEARCH (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct metapage*,TYPE_2__*,int) ; 
 size_t* DT_GETSTBL (TYPE_2__*) ; 
 int /*<<< orphan*/  DT_PUTPAGE (struct metapage*) ; 
 int L2DTSLOTSIZE ; 
 int /*<<< orphan*/  PSIZE ; 
 int /*<<< orphan*/  dtDeleteEntry (TYPE_2__*,int,struct dt_lock**) ; 
 int dtDeleteUp (int /*<<< orphan*/ ,struct inode*,struct metapage*,TYPE_2__*,struct btstack*) ; 
 int dtSearch (struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*,int) ; 
 int /*<<< orphan*/  free_index (int /*<<< orphan*/ ,struct inode*,int,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  modify_index (int /*<<< orphan*/ ,struct inode*,int,int /*<<< orphan*/ ,int,struct metapage**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int tlckDTREE ; 
 int tlckENTRY ; 
 scalar_t__ txLinelock (struct dt_lock*) ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 

int dtDelete(tid_t tid,
	 struct inode *ip, struct component_name * key, ino_t * ino, int flag)
{
	int rc = 0;
	s64 bn;
	struct metapage *mp, *imp;
	dtpage_t *p;
	int index;
	struct btstack btstack;
	struct dt_lock *dtlck;
	struct tlock *tlck;
	struct lv *lv;
	int i;
	struct ldtentry *ldtentry;
	u8 *stbl;
	u32 table_index, next_index;
	struct metapage *nmp;
	dtpage_t *np;

	/*
	 *	search for the entry to delete:
	 *
	 * dtSearch() returns (leaf page pinned, index at which to delete).
	 */
	if ((rc = dtSearch(ip, key, ino, &btstack, flag)))
		return rc;

	/* retrieve search result */
	DT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	/*
	 * We need to find put the index of the next entry into the
	 * directory index table in order to resume a readdir from this
	 * entry.
	 */
	if (DO_INDEX(ip)) {
		stbl = DT_GETSTBL(p);
		ldtentry = (struct ldtentry *) & p->slot[stbl[index]];
		table_index = le32_to_cpu(ldtentry->index);
		if (index == (p->header.nextindex - 1)) {
			/*
			 * Last entry in this leaf page
			 */
			if ((p->header.flag & BT_ROOT)
			    || (p->header.next == 0))
				next_index = -1;
			else {
				/* Read next leaf page */
				DT_GETPAGE(ip, le64_to_cpu(p->header.next),
					   nmp, PSIZE, np, rc);
				if (rc)
					next_index = -1;
				else {
					stbl = DT_GETSTBL(np);
					ldtentry =
					    (struct ldtentry *) & np->
					    slot[stbl[0]];
					next_index =
					    le32_to_cpu(ldtentry->index);
					DT_PUTPAGE(nmp);
				}
			}
		} else {
			ldtentry =
			    (struct ldtentry *) & p->slot[stbl[index + 1]];
			next_index = le32_to_cpu(ldtentry->index);
		}
		free_index(tid, ip, table_index, next_index);
	}
	/*
	 * the leaf page becomes empty, delete the page
	 */
	if (p->header.nextindex == 1) {
		/* delete empty page */
		rc = dtDeleteUp(tid, ip, mp, p, &btstack);
	}
	/*
	 * the leaf page has other entries remaining:
	 *
	 * delete the entry from the leaf page.
	 */
	else {
		BT_MARK_DIRTY(mp, ip);
		/*
		 * acquire a transaction lock on the leaf page
		 */
		tlck = txLock(tid, ip, mp, tlckDTREE | tlckENTRY);
		dtlck = (struct dt_lock *) & tlck->lock;

		/*
		 * Do not assume that dtlck->index will be zero.  During a
		 * rename within a directory, this transaction may have
		 * modified this page already when adding the new entry.
		 */

		/* linelock header */
		if (dtlck->index >= dtlck->maxcnt)
			dtlck = (struct dt_lock *) txLinelock(dtlck);
		lv = & dtlck->lv[dtlck->index];
		lv->offset = 0;
		lv->length = 1;
		dtlck->index++;

		/* linelock stbl of non-root leaf page */
		if (!(p->header.flag & BT_ROOT)) {
			if (dtlck->index >= dtlck->maxcnt)
				dtlck = (struct dt_lock *) txLinelock(dtlck);
			lv = & dtlck->lv[dtlck->index];
			i = index >> L2DTSLOTSIZE;
			lv->offset = p->header.stblindex + i;
			lv->length =
			    ((p->header.nextindex - 1) >> L2DTSLOTSIZE) -
			    i + 1;
			dtlck->index++;
		}

		/* free the leaf entry */
		dtDeleteEntry(p, index, &dtlck);

		/*
		 * Update directory index table for entries moved in stbl
		 */
		if (DO_INDEX(ip) && index < p->header.nextindex) {
			s64 lblock;

			imp = NULL;
			stbl = DT_GETSTBL(p);
			for (i = index; i < p->header.nextindex; i++) {
				ldtentry =
				    (struct ldtentry *) & p->slot[stbl[i]];
				modify_index(tid, ip,
					     le32_to_cpu(ldtentry->index),
					     bn, i, &imp, &lblock);
			}
			if (imp)
				release_metapage(imp);
		}

		DT_PUTPAGE(mp);
	}

	return rc;
}