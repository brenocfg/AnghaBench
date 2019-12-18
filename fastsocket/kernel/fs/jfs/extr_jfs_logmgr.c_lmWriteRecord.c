#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tlock {int flag; int type; int /*<<< orphan*/  lock; int /*<<< orphan*/  ip; TYPE_1__* mp; } ;
struct tblock {int clsn; int pn; int eor; int /*<<< orphan*/  cqueue; struct lbuf* bp; int /*<<< orphan*/  flag; } ;
struct lvd {int offset; int length; } ;
struct lv {int length; int offset; } ;
struct lrd {int length; int type; } ;
struct logpage {int dummy; } ;
struct linelock {int l2linesize; int index; int maxcnt; int next; struct lv* lv; } ;
struct lbuf {int l_eor; scalar_t__ l_ldata; } ;
struct jfs_log {int eor; int page; struct lbuf* bp; int /*<<< orphan*/  cqueue; } ;
struct inlinelock {int /*<<< orphan*/  pxd; } ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_xtroot; int /*<<< orphan*/  i_dtroot; } ;
struct TYPE_5__ {int /*<<< orphan*/  commit; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 TYPE_3__* JFS_IP (int /*<<< orphan*/ ) ; 
 int L2LOGPSIZE ; 
 int /*<<< orphan*/  LOGGC_LOCK (struct jfs_log*) ; 
 int /*<<< orphan*/  LOGGC_UNLOCK (struct jfs_log*) ; 
 int LOGPHDRSIZE ; 
 int LOGPSIZE ; 
 int LOGPTLRSIZE ; 
 int LOGRDSIZE ; 
 int LOG_COMMIT ; 
 int cpu_to_le16 (int) ; 
 struct inlinelock* inlinelock ; 
 int /*<<< orphan*/  jfs_err (char*,struct tlock*) ; 
 int /*<<< orphan*/  jfs_info (char*,int,...) ; 
 int /*<<< orphan*/  le16_to_cpu (int) ; 
 scalar_t__ lid_to_tlock (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lmNextPage (struct jfs_log*) ; 
 TYPE_2__ lmStat ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  tblkGC_QUEUE ; 
 int tlckDTREE ; 
 int tlckINLINELOCK ; 
 int tlckINODELOCK ; 
 int tlckPAGELOCK ; 

__attribute__((used)) static int
lmWriteRecord(struct jfs_log * log, struct tblock * tblk, struct lrd * lrd,
	      struct tlock * tlck)
{
	int lsn = 0;		/* end-of-log address */
	struct lbuf *bp;	/* dst log page buffer */
	struct logpage *lp;	/* dst log page */
	caddr_t dst;		/* destination address in log page */
	int dstoffset;		/* end-of-log offset in log page */
	int freespace;		/* free space in log page */
	caddr_t p;		/* src meta-data page */
	caddr_t src;
	int srclen;
	int nbytes;		/* number of bytes to move */
	int i;
	int len;
	struct linelock *linelock;
	struct lv *lv;
	struct lvd *lvd;
	int l2linesize;

	len = 0;

	/* retrieve destination log page to write */
	bp = (struct lbuf *) log->bp;
	lp = (struct logpage *) bp->l_ldata;
	dstoffset = log->eor;

	/* any log data to write ? */
	if (tlck == NULL)
		goto moveLrd;

	/*
	 *	move log record data
	 */
	/* retrieve source meta-data page to log */
	if (tlck->flag & tlckPAGELOCK) {
		p = (caddr_t) (tlck->mp->data);
		linelock = (struct linelock *) & tlck->lock;
	}
	/* retrieve source in-memory inode to log */
	else if (tlck->flag & tlckINODELOCK) {
		if (tlck->type & tlckDTREE)
			p = (caddr_t) &JFS_IP(tlck->ip)->i_dtroot;
		else
			p = (caddr_t) &JFS_IP(tlck->ip)->i_xtroot;
		linelock = (struct linelock *) & tlck->lock;
	}
#ifdef	_JFS_WIP
	else if (tlck->flag & tlckINLINELOCK) {

		inlinelock = (struct inlinelock *) & tlck;
		p = (caddr_t) & inlinelock->pxd;
		linelock = (struct linelock *) & tlck;
	}
#endif				/* _JFS_WIP */
	else {
		jfs_err("lmWriteRecord: UFO tlck:0x%p", tlck);
		return 0;	/* Probably should trap */
	}
	l2linesize = linelock->l2linesize;

      moveData:
	ASSERT(linelock->index <= linelock->maxcnt);

	lv = linelock->lv;
	for (i = 0; i < linelock->index; i++, lv++) {
		if (lv->length == 0)
			continue;

		/* is page full ? */
		if (dstoffset >= LOGPSIZE - LOGPTLRSIZE) {
			/* page become full: move on to next page */
			lmNextPage(log);

			bp = log->bp;
			lp = (struct logpage *) bp->l_ldata;
			dstoffset = LOGPHDRSIZE;
		}

		/*
		 * move log vector data
		 */
		src = (u8 *) p + (lv->offset << l2linesize);
		srclen = lv->length << l2linesize;
		len += srclen;
		while (srclen > 0) {
			freespace = (LOGPSIZE - LOGPTLRSIZE) - dstoffset;
			nbytes = min(freespace, srclen);
			dst = (caddr_t) lp + dstoffset;
			memcpy(dst, src, nbytes);
			dstoffset += nbytes;

			/* is page not full ? */
			if (dstoffset < LOGPSIZE - LOGPTLRSIZE)
				break;

			/* page become full: move on to next page */
			lmNextPage(log);

			bp = (struct lbuf *) log->bp;
			lp = (struct logpage *) bp->l_ldata;
			dstoffset = LOGPHDRSIZE;

			srclen -= nbytes;
			src += nbytes;
		}

		/*
		 * move log vector descriptor
		 */
		len += 4;
		lvd = (struct lvd *) ((caddr_t) lp + dstoffset);
		lvd->offset = cpu_to_le16(lv->offset);
		lvd->length = cpu_to_le16(lv->length);
		dstoffset += 4;
		jfs_info("lmWriteRecord: lv offset:%d length:%d",
			 lv->offset, lv->length);
	}

	if ((i = linelock->next)) {
		linelock = (struct linelock *) lid_to_tlock(i);
		goto moveData;
	}

	/*
	 *	move log record descriptor
	 */
      moveLrd:
	lrd->length = cpu_to_le16(len);

	src = (caddr_t) lrd;
	srclen = LOGRDSIZE;

	while (srclen > 0) {
		freespace = (LOGPSIZE - LOGPTLRSIZE) - dstoffset;
		nbytes = min(freespace, srclen);
		dst = (caddr_t) lp + dstoffset;
		memcpy(dst, src, nbytes);

		dstoffset += nbytes;
		srclen -= nbytes;

		/* are there more to move than freespace of page ? */
		if (srclen)
			goto pageFull;

		/*
		 * end of log record descriptor
		 */

		/* update last log record eor */
		log->eor = dstoffset;
		bp->l_eor = dstoffset;
		lsn = (log->page << L2LOGPSIZE) + dstoffset;

		if (lrd->type & cpu_to_le16(LOG_COMMIT)) {
			tblk->clsn = lsn;
			jfs_info("wr: tclsn:0x%x, beor:0x%x", tblk->clsn,
				 bp->l_eor);

			INCREMENT(lmStat.commit);	/* # of commit */

			/*
			 * enqueue tblock for group commit:
			 *
			 * enqueue tblock of non-trivial/synchronous COMMIT
			 * at tail of group commit queue
			 * (trivial/asynchronous COMMITs are ignored by
			 * group commit.)
			 */
			LOGGC_LOCK(log);

			/* init tblock gc state */
			tblk->flag = tblkGC_QUEUE;
			tblk->bp = log->bp;
			tblk->pn = log->page;
			tblk->eor = log->eor;

			/* enqueue transaction to commit queue */
			list_add_tail(&tblk->cqueue, &log->cqueue);

			LOGGC_UNLOCK(log);
		}

		jfs_info("lmWriteRecord: lrd:0x%04x bp:0x%p pn:%d eor:0x%x",
			le16_to_cpu(lrd->type), log->bp, log->page, dstoffset);

		/* page not full ? */
		if (dstoffset < LOGPSIZE - LOGPTLRSIZE)
			return lsn;

	      pageFull:
		/* page become full: move on to next page */
		lmNextPage(log);

		bp = (struct lbuf *) log->bp;
		lp = (struct logpage *) bp->l_ldata;
		dstoffset = LOGPHDRSIZE;
		src += nbytes;
	}

	return lsn;
}