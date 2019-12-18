#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int tid_t ;
struct tblock {scalar_t__ next; int last; int xflag; int flag; int lsn; scalar_t__ logtid; struct super_block* sb; } ;
struct super_block {int dummy; } ;
struct jfs_log {int /*<<< orphan*/  active; scalar_t__ logtid; int /*<<< orphan*/  syncwait; int /*<<< orphan*/  flag; } ;
struct TYPE_8__ {struct jfs_log* log; } ;
struct TYPE_7__ {scalar_t__ tlocksInUse; int freetid; int /*<<< orphan*/  freewait; int /*<<< orphan*/  lowlockwait; } ;
struct TYPE_6__ {int /*<<< orphan*/  txBegin_freetid; int /*<<< orphan*/  txBegin_lockslow; int /*<<< orphan*/  txBegin_barrier; int /*<<< orphan*/  txBegin; } ;
struct TYPE_5__ {int /*<<< orphan*/  ntid; int /*<<< orphan*/  maxtid; } ;

/* Variables and functions */
 int COMMIT_FORCE ; 
 int /*<<< orphan*/  HIGHWATERMARK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 TYPE_4__* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  TXN_LOCK () ; 
 int /*<<< orphan*/  TXN_SLEEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TXN_UNLOCK () ; 
 TYPE_3__ TxAnchor ; 
 scalar_t__ TxLockVHWM ; 
 TYPE_2__ TxStat ; 
 int /*<<< orphan*/  jfs_info (char*,...) ; 
 int /*<<< orphan*/  log_QUIESCE ; 
 int /*<<< orphan*/  log_SYNCBARRIER ; 
 TYPE_1__ stattx ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tblock* tid_to_tblock (int) ; 

tid_t txBegin(struct super_block *sb, int flag)
{
	tid_t t;
	struct tblock *tblk;
	struct jfs_log *log;

	jfs_info("txBegin: flag = 0x%x", flag);
	log = JFS_SBI(sb)->log;

	TXN_LOCK();

	INCREMENT(TxStat.txBegin);

      retry:
	if (!(flag & COMMIT_FORCE)) {
		/*
		 * synchronize with logsync barrier
		 */
		if (test_bit(log_SYNCBARRIER, &log->flag) ||
		    test_bit(log_QUIESCE, &log->flag)) {
			INCREMENT(TxStat.txBegin_barrier);
			TXN_SLEEP(&log->syncwait);
			goto retry;
		}
	}
	if (flag == 0) {
		/*
		 * Don't begin transaction if we're getting starved for tlocks
		 * unless COMMIT_FORCE or COMMIT_INODE (which may ultimately
		 * free tlocks)
		 */
		if (TxAnchor.tlocksInUse > TxLockVHWM) {
			INCREMENT(TxStat.txBegin_lockslow);
			TXN_SLEEP(&TxAnchor.lowlockwait);
			goto retry;
		}
	}

	/*
	 * allocate transaction id/block
	 */
	if ((t = TxAnchor.freetid) == 0) {
		jfs_info("txBegin: waiting for free tid");
		INCREMENT(TxStat.txBegin_freetid);
		TXN_SLEEP(&TxAnchor.freewait);
		goto retry;
	}

	tblk = tid_to_tblock(t);

	if ((tblk->next == 0) && !(flag & COMMIT_FORCE)) {
		/* Don't let a non-forced transaction take the last tblk */
		jfs_info("txBegin: waiting for free tid");
		INCREMENT(TxStat.txBegin_freetid);
		TXN_SLEEP(&TxAnchor.freewait);
		goto retry;
	}

	TxAnchor.freetid = tblk->next;

	/*
	 * initialize transaction
	 */

	/*
	 * We can't zero the whole thing or we screw up another thread being
	 * awakened after sleeping on tblk->waitor
	 *
	 * memset(tblk, 0, sizeof(struct tblock));
	 */
	tblk->next = tblk->last = tblk->xflag = tblk->flag = tblk->lsn = 0;

	tblk->sb = sb;
	++log->logtid;
	tblk->logtid = log->logtid;

	++log->active;

	HIGHWATERMARK(stattx.maxtid, t);	/* statistics */
	INCREMENT(stattx.ntid);	/* statistics */

	TXN_UNLOCK();

	jfs_info("txBegin: returning tid = %d", t);

	return t;
}