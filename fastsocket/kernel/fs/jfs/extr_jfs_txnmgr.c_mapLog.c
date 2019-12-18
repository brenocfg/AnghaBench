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
typedef  int /*<<< orphan*/  ulong ;
struct tlock {int type; int /*<<< orphan*/  flag; int /*<<< orphan*/  lock; } ;
struct tblock {int dummy; } ;
struct pxd_lock {int index; int flag; int /*<<< orphan*/  pxd; } ;
struct TYPE_5__ {int /*<<< orphan*/  pxd; void* nxd; void* type; } ;
struct TYPE_4__ {int /*<<< orphan*/  pxd; } ;
struct TYPE_6__ {TYPE_2__ updatemap; TYPE_1__ redopage; } ;
struct lrd {void* backchain; TYPE_3__ log; void* type; } ;
struct jfs_log {int dummy; } ;
typedef  int /*<<< orphan*/  pxd_t ;

/* Variables and functions */
 int LOG_ALLOCPXD ; 
 int LOG_FREEPXD ; 
 int LOG_NOREDOPAGE ; 
 int LOG_UPDATEMAP ; 
 scalar_t__ addressPXD (int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lengthPXD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lmLog (struct jfs_log*,struct tblock*,struct lrd*,int /*<<< orphan*/ *) ; 
 int mlckALLOCPXD ; 
 int tlckRELOCATE ; 
 int /*<<< orphan*/  tlckUPDATEMAP ; 

__attribute__((used)) static void mapLog(struct jfs_log * log, struct tblock * tblk, struct lrd * lrd,
		   struct tlock * tlck)
{
	struct pxd_lock *pxdlock;
	int i, nlock;
	pxd_t *pxd;

	/*
	 *	page relocation: free the source page extent
	 *
	 * a maplock for txUpdateMap() for free of the page
	 * has been formatted at txLock() time saving the src
	 * relocated page address;
	 */
	if (tlck->type & tlckRELOCATE) {
		/* log LOG_NOREDOPAGE of the old relocated page
		 * for logredo() to start NoRedoPage filter;
		 */
		lrd->type = cpu_to_le16(LOG_NOREDOPAGE);
		pxdlock = (struct pxd_lock *) & tlck->lock;
		pxd = &lrd->log.redopage.pxd;
		*pxd = pxdlock->pxd;
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, NULL));

		/* (N.B. currently, logredo() does NOT update bmap
		 * for free of the page itself for (LOG_XTREE|LOG_NOREDOPAGE);
		 * if page free from relocation, LOG_UPDATEMAP log is
		 * specifically generated now for logredo()
		 * to update bmap for free of src relocated page;
		 * (new flag LOG_RELOCATE may be introduced which will
		 * inform logredo() to start NORedoPage filter and also
		 * update block allocation map at the same time, thus
		 * avoiding an extra log write);
		 */
		lrd->type = cpu_to_le16(LOG_UPDATEMAP);
		lrd->log.updatemap.type = cpu_to_le16(LOG_FREEPXD);
		lrd->log.updatemap.nxd = cpu_to_le16(1);
		lrd->log.updatemap.pxd = pxdlock->pxd;
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, NULL));

		/* a maplock for txUpdateMap() for free of the page
		 * has been formatted at txLock() time;
		 */
		tlck->flag |= tlckUPDATEMAP;
		return;
	}
	/*

	 * Otherwise it's not a relocate request
	 *
	 */
	else {
		/* log LOG_UPDATEMAP for logredo() to update bmap for
		 * free of truncated/relocated delta extent of the data;
		 * e.g.: external EA extent, relocated/truncated extent
		 * from xtTailgate();
		 */
		lrd->type = cpu_to_le16(LOG_UPDATEMAP);
		pxdlock = (struct pxd_lock *) & tlck->lock;
		nlock = pxdlock->index;
		for (i = 0; i < nlock; i++, pxdlock++) {
			if (pxdlock->flag & mlckALLOCPXD)
				lrd->log.updatemap.type =
				    cpu_to_le16(LOG_ALLOCPXD);
			else
				lrd->log.updatemap.type =
				    cpu_to_le16(LOG_FREEPXD);
			lrd->log.updatemap.nxd = cpu_to_le16(1);
			lrd->log.updatemap.pxd = pxdlock->pxd;
			lrd->backchain =
			    cpu_to_le32(lmLog(log, tblk, lrd, NULL));
			jfs_info("mapLog: xaddr:0x%lx xlen:0x%x",
				 (ulong) addressPXD(&pxdlock->pxd),
				 lengthPXD(&pxdlock->pxd));
		}

		/* update bmap */
		tlck->flag |= tlckUPDATEMAP;
	}
}