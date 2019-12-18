#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct timeval {scalar_t__ tv_sec; } ;
struct TYPE_4__ {int lm_xid; } ;
struct TYPE_5__ {TYPE_1__ lmr_msg; } ;
typedef  TYPE_2__ LOCKD_MSG_REQUEST ;

/* Variables and functions */
 TYPE_2__* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int /*<<< orphan*/  nfs_lock_msg_queue ; 
 scalar_t__ nfs_lockdmsg_find_by_xid (int) ; 
 int nfs_lockxid ; 
 int /*<<< orphan*/  nfs_pendlockq ; 

uint64_t
nfs_lockxid_get(void)
{
	LOCKD_MSG_REQUEST *mr;

	/* derive initial lock xid from system time */
	if (!nfs_lockxid) {
		/*
		 * Note: it's OK if this code inits nfs_lockxid to 0 (for example,
		 * due to a broken clock) because we immediately increment it
		 * and we guarantee to never use xid 0.  So, nfs_lockxid should only
		 * ever be 0 the first time this function is called.
		 */
		struct timeval tv;
		microtime(&tv);
		nfs_lockxid = (uint64_t)tv.tv_sec << 12;
	}

	/* make sure we get a unique xid */
	do {
		/* Skip zero xid if it should ever happen.  */
		if (++nfs_lockxid == 0)
			nfs_lockxid++;
		if (!(mr = TAILQ_LAST(&nfs_pendlockq, nfs_lock_msg_queue)) ||
		     (mr->lmr_msg.lm_xid < nfs_lockxid)) {
			/* fast path: empty queue or new largest xid */
			break;
		}
		/* check if xid is already in use */
	} while (nfs_lockdmsg_find_by_xid(nfs_lockxid));

	return nfs_lockxid;
}